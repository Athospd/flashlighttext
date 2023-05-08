tkn_to_idx <- function(spelling, token_dict, maxReps = 0){
  result <- c()
  for(token in spelling) {
    result <- c(result, token_dict$get_index(token))
  }
  return(pack_replabels(result, token_dict, maxReps))
}
  
test_that("load_words", {
  # emissions ---------------------------------------------------------------
  
  Emissions <- function(
    emission, # A column-major tensor with shape T x N.
    nFrames = 0,
    nTokens = 0
  ) {
    list(emission = emission, nFrames = nFrames, nTokens = nTokens)
  }
  
  sys_file <- function(file) system.file(file, package = "flashlighttext")
  
  read_bin <- function(file, type) {
    readBin(sys_file(file), type, n = 10000)
  }
  
  # emissionUnit = Emissions()
  c(T, N) %<-% read_bin("TN.bin", "integer")
  emissions <- read_bin("emission.bin", "numeric")
  transitions <- read_bin("transition.bin", "numeric")
  lexicon <- load_words(sys_file("words.lst"))
  word_dict <- create_word_dict(lexicon)
  token_dict <- Dictionary$new(sys_file("letters.lst"))
  token_dict$add_entry("<1>")
  lm <- KenLM$new(sys_file("lm.arpa"), word_dict)
  flashlighttext:::explore_kenlm(lm$ptr)
  
  # test LM
  sentence <- c("the", "cat", "sat", "on", "the", "mat")
  lm_state <- lm$start(FALSE)
  total_score <- 0
  lm_score_target <- c(-1.05971, -4.19448, -3.33383, -2.76726, -1.16237, -4.64589)
  
  # a <- lm$score(lm_state, word_dict$get_index(sentence[1]))
  # iterate over words in the sentence
  for(i in seq_along(sentence)) {
    c(lm_state, lm_score) %<-% lm$score(lm_state, word_dict$get_index(sentence[i]))
    expect_equal(lm_score, lm_score_target[i], tolerance = 1e-4)
    total_score = total_score + lm_score
  }
  
  # move lm to the final state, the score returned is for eos
  c(lm_state, lm_score) %<-% lm$finish(lm_state)
  total_score = total_score + lm_score
  expect_equal(total_score, -19.5123, tolerance = 1e-4)

  # build trie
  separator_idx <- token_dict$get_index("|")
  unk_idx <- word_dict$get_index("<unk>")
  trie <- Trie$new(token_dict$index_size(), separator_idx)
  start_state <- lm$start(FALSE)
  for(word in names(lexicon)) {
    spellings <- if(word != "<unk>") lexicon[[word]][[1]] else list()
    usr_idx <- word_dict$get_index(word)
    score <- lm$score(start_state, usr_idx)[[2]]
    
    cat(word, " - ", usr_idx, " - ", score, "\n")
    
    for(spelling in spellings) {
      spelling_idxs = tkn_to_idx(spelling, token_dict, 1)
      cat("   >> ", spelling, " - ", spelling_idxs, "\n")
      trie$insert(spelling_idxs, usr_idx, score)
    }
  }
  trie$smear(SmearingMode$MAX)
  
  trie_score_target <- c(-1.05971, -2.87742, -2.64553, -3.05081, -1.05971, -3.08968)
  for(i in seq_along(sentence)) {
    word <- sentence[i]
    # max_reps should be 1; using 0 here to match DecoderTest bug
    word_tensor <- tkn_to_idx(strsplit(word, "")[[1]], token_dict, 1)
    node = trie$search(word_tensor)
    expect_equal(node$max_score, trie_score_target[i], tolerance = 1e-4)
  }
    
})
