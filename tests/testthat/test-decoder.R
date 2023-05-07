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

})
