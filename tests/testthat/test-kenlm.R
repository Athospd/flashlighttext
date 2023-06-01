sys_file <- function(file) system.file(file, package = "flashlighttext")
read_bin <- function(file, type, size) readBin(sys_file(file), size = size, type, n = 10000)

test_that("kenlm", {
  lexicon <- load_words(sys_file("words.lst")) 
  word_dict <- create_word_dict(lexicon) 
  lm <- KenLM$new(sys_file("lm.arpa"), word_dict) 
  lm_state <- lm$start(FALSE) 
  c(lm_state, lm_score) %<-% lm$score(lm_state, 0) 
  
  expect_s3_class(lm, "KenLM")
  expect_equal(class(lm_score), "numeric")
  
  word_dict2 <- create_word_dict(list(
    "hello" = list("h", "e", "l", "l", "o", "|"),
    "world" = list("w", "o", "r", "l", "d", "|"),
    "<unk>" = list()
  )) 
  lm2 <- KenLM$new(sys_file("lm.arpa"), word_dict2) 
  
  expect_equal(sort(lm2$usrTknDict$map_indices_to_entries(0:2)), c("<unk>", "hello", "world"))
})
