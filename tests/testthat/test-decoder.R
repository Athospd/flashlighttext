test_that("load_words", {
  data_dir <- "include/flashlight/lib/text/test/decoder/data/"
  lexicon <- load_words(system.file(file.path(data_dir, "words.lst"), package = "flashlighttext"), 1000)
  tokenDict <- Dictionary$new(system.file(file.path(data_dir,  "letters.lst"), package = "flashlighttext"))
  tokenDict$add_entry("<1>")
  wordDict <- create_word_dict(lexicon)
  wordDict$ptr
  expect_equal(wordDict$index_size(), 1001)
  expect_equal(wordDict$entry_size(), 1001)
})
