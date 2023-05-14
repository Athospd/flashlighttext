sys_file <- function(file) system.file(file, package = "flashlighttext")
read_bin <- function(file, type, size) readBin(sys_file(file), size = size, type, n = 10000)

test_that("kenlm", {
  lexicon <- load_words(sys_file("words.lst")) 
  word_dict <- create_word_dict(lexicon) 
  lm <- KenLM$new(sys_file("lm.arpa"), word_dict) 
  lm_state <- lm$start(FALSE) 
  c(lm_state, lm_score) %<-% lm$score(lm_state, 0) 
  
  expect_s3_class(lm, "KenLM")
  expect_equal(lm_score, -3.089679)
})
