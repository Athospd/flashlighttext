test_that("lexicon_seq2seq_decoder", {
  opts <- LexiconSeq2SeqDecoderOptions$new(
    beam_size = 2,
    beam_size_token = 4,
    beam_threshold = 1000,
    lm_weight = 0,
    word_score = 0,
    eos_score = 0,
    log_add = FALSE
  )
  
  lm <- ZeroLM$new()
  lexicon <- list(
    "hello" = list(c("h", "e", "l", "l", "o", "|")),
    "world" = list(c("w", "o", "r", "l", "d", "|")),
    "<unk>" = list()
  )
  word_dict <- create_word_dict(lexicon)
  token_dict <- Dictionary$new(c("h", "e", "l", "o", "|", "w", "r", "d", "<unk>")) 
  token_dict$add_entry("<1>")
  trie <- build_trie(
    lm = lm,
    token_dict = token_dict,
    lexicon = lexicon, 
    word_dict = word_dict,
    separator_idx = token_dict$get_index("|")
  )
  
  expect_error(decoder <- LexiconSeq2SeqDecoder$new(
    options = opts,
    trie = trie,
    lm = lm,
    eos = 9,
    emitting_model_update_func = update_func,
    max_output_length = 3,
    is_lm_token = TRUE
  ))
})
