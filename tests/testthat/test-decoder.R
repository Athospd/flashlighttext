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
})
