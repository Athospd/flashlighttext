
<!-- README.md is generated from README.Rmd. Please edit that file -->

# flashlighttext

<!-- badges: start -->

[![Lifecycle:
experimental](https://img.shields.io/badge/lifecycle-experimental-orange.svg)](https://lifecycle.r-lib.org/articles/stages.html#experimental)
[![R-CMD-check](https://github.com/Athospd/flashlighttext/actions/workflows/R-CMD-check.yaml/badge.svg)](https://github.com/Athospd/flashlighttext/actions/workflows/R-CMD-check.yaml)
[![CRAN
status](https://www.r-pkg.org/badges/version/flashlighttext)](https://CRAN.R-project.org/package=flashlighttext)
<!-- badges: end -->

This package provides bindings to part of the [Flashlight’s Text C++
lib](https://github.com/flashlight/text). It contains beam search
decoder, the [KenLM](https://github.com/kpu/kenlm/) language model built
in, and dictionary components.

It is a translation to R of the Python’s bindings lib by [Flashlight
group](https://github.com/flashlight) (See [flashlight-text
repo](https://github.com/flashlight/text)).

## Installation

From CRAN:

``` r
install.packages("flashlighttext")
```

You can install the development version of flashlighttext from
[GitHub](https://github.com/athospd/flashlighttext) with:

``` r
remotes::install_github("athospd/flashlighttext")
```

## Examples

This text is a translation from [this
tutorial](https://github.com/flashlight/text/tree/main/bindings/python)
by [Jacob Kahn.](https://github.com/jacobkahn)

``` r
library(flashlighttext)
```

### Beam Search Decoder

Bindings for the lexicon and lexicon-free beam search decoders are
supported for CTC/ASG models only (no seq2seq model support).
Out-of-the-box language model support includes KenLM; users can define
custom a language model in Python and use it for decoding; see the
documentation below.

To run decoder one first should define options:

``` r
# for lexicon-based decoder
options = LexiconDecoderOptions$new(
  beam_size, # number of top hypothesis to preserve at each decoding step
  token_beam_size, # restrict number of tokens by top am scores (if you have a huge token set)
  beam_threshold, # preserve a hypothesis only if its score is not far away from the current best hypothesis score
  lm_weight, # language model weight for LM score
  word_score, # score for words appearance in the transcription
  unk_score, # score for unknown word appearance in the transcription
  sil_score, # score for silence appearance in the transcription
  log_add, # the way how to combine scores during hypotheses merging (log add operation, max)
  criterion_type # supports only CriterionTypes$ASG or CriterionTypes$CTC
)

# for lexicon free-based decoder
options = LexiconFreeDecoderOptions$new(
  beam_size, # number of top hypothesis to preserve at each decoding step
  token_beam_size, # restrict number of tokens by top am scores (if you have a huge token set)
  beam_threshold, # preserve a hypothesis only if its score is not far away from the current best hypothesis score
  lm_weight, # language model weight for LM score
  sil_score, # score for silence appearance in the transcription
  log_add, # the way how to combine scores during hypotheses merging (log add operation, max)
  criterion_type # supports only CriterionTypes$ASG or CriterionTypes$CTC
)
```

Now, prepare a tokens dictionary (tokens for which a model returns
probability for each frame) and a lexicon (mapping between words and
their spellings within a tokens set).

For further details on tokens and lexicon file formats, see the [Data
Preparation](https://github.com/flashlight/flashlight/tree/main/flashlight/app/asr#data-preparation)
documentation in [Flashlight](https://github.com/flashlight/flashlight).

``` r
tokens_dict <- Dictionary$new("path/tokens.txt")
tokens_dict$add_entry("<1>") 
# for ASG add used repetition symbols, for example
# tokens_dict$add_entry("1")
# tokens_dict$add_entry("2")

lexicon <- load_words("words.txt") # returns a list
lexicon[1:2]
```

    $handsets
    $handsets[[1]]
    [1] "h" "a" "n" "d" "s" "e" "t" "s" "|"


    $primus
    $primus[[1]]
    [1] "p" "r" "i" "m" "u" "s" "|"

``` r
word_dict <- create_word_dict(lexicon) # returns Dictionary
```

To create a KenLM language model, use:

``` r
lm <- KenLM$new("path/lm.arpa", word_dict) # or "path/lm.bin"
```

    Loading the LM will be faster if you build a binary file.
    Reading C:/Users/ap_da/AppData/Local/R/win-library/4.3/flashlighttext/lm.arpa
    ----5---10---15---20---25---30---35---40---45---50---55---60---65---70---75---80---85---90---95--100
    ****************************************************************************************************

Get the unknown and silence token indices from the token and word
dictionaries to pass to the decoder:

``` r
sil_idx <- tokens_dict$get_index("|")    # 0
unk_idx <- word_dict$get_index("<unk>")  # 21207
```

Now, define the lexicon `Trie` to restrict the beam search decoder
search:

``` r
# build_trie()
trie <- Trie$new(tokens_dict$index_size(), sil_idx)
start_state <- lm$start(FALSE)
lexicon <- list2env(lexicon, hash = TRUE)
for(word in names(lexicon)) {
  spellings <- lexicon[[word]]
  usr_idx <- word_dict$get_index(word)
  score <- lm$score(start_state, usr_idx)[[2]]
  for(spelling in spellings) {
    # convert spelling string into vector of indices
    tokens_dict$map_entries_to_indices(spelling) %>%
      pack_replabels(tokens_dict, 1) %>%
      trie$insert(usr_idx, score)
  }
}

# propagate word score to each spelling node to have some lm proxy score in each node.
trie$smear(SmearingModes$MAX)
```

Finally, we can run lexicon-based decoder:
