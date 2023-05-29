sys_file <- function(file) system.file(file, package = "flashlighttext")
read_bin <- function(file, type, size) readBin(sys_file(file), size = size, type, n = 10000)
tkn_to_idx <- function(spelling, token_dict, maxReps = 0) {
  result <- c()
  for(token in spelling) {
    result <- c(result, token_dict$get_index(token))
  }
  return(pack_replabels(result, token_dict, maxReps))
}

test_that("lexicon_decoder", {
  # emissions ---------------------------------------------------------------
  
  c(T, N) %<-% read.table(sys_file("TN.txt"))
  emissions <- read_bin("emission.bin", "numeric", size = 4) 
  transitions <- read_bin("transition.bin", "numeric", size = 4) 
  lexicon <- load_words(sys_file("words.lst")) 
  word_dict <- create_word_dict(lexicon) 
  token_dict <- Dictionary$new(sys_file("letters.lst")) 
  token_dict$add_entry("<1>") 
  lm <- KenLM$new(sys_file("lm.arpa"), word_dict) 
  
  # test LM
  sentence <- c("the", "cat", "sat", "on", "the", "mat") 
  lm_state <- lm$start(FALSE) 
  total_score <- 0
  lm_score_target <- c(-1.05971, -4.19448, -3.33383, -2.76726, -1.16237, -4.64589)
  
  # iterate over words in the sentence
  for(i in seq_along(sentence)) { 
    c(lm_state, lm_score) %<-% lm$score(lm_state, word_dict$get_index(sentence[i])) 
    expect_equal(lm_score, lm_score_target[i], tolerance = 1e-4) 
    total_score = total_score + lm_score 
  }
  total_score 
  
  # move lm to the final state, the score returned is for eos
  c(lm_state, lm_score) %<-% lm$finish(lm_state) 
  total_score = total_score + lm_score 
  expect_equal(total_score, -19.5123, tolerance = 1e-4) 
  
  # build trie
  separator_idx <- token_dict$get_index("|") 
  unk_idx <- word_dict$get_index("<unk>") 
  trie <- build_trie(
    lm = lm,
    token_dict = token_dict,
    lexicon = lexicon,
    word_dict = word_dict,
    separator_idx = separator_idx
  )
  
  trie_score_target <- c(-1.05971, -2.87742, -2.64553, -3.05081, -1.05971, -3.08968)
  for(i in seq_along(sentence)) {
    word <- sentence[i]
    # max_reps should be 1; using 0 here to match DecoderTest bug
    word_tensor <- tkn_to_idx(strsplit(word, "")[[1]], token_dict, 1)
    node <- trie$search(word_tensor)
    expect_equal(node$max_score(), trie_score_target[i], tolerance = 1e-4)
  }
  
  # decoder
  opts <- LexiconDecoderOptions$new(
    beam_size = 2500,
    beam_size_token = 25000,
    beam_threshold = 100.0,
    lm_weight = 2.0,
    word_score = 2.0,
    unk_score = -Inf,
    sil_score = -1,
    log_add = FALSE,
    criterion_type = CriterionTypes$ASG
  )
  
  decoder <- LexiconDecoder$new(
    options = opts,
    trie = trie,
    lm = lm,
    sil_token_idx = separator_idx,
    blank_token_idx = -1,
    unk_token_idx = unk_idx,
    transitions = transitions,
    is_lm_token = FALSE
  )
  
  # run decoding
  results <- decoder$decode(emissions, T, N)
  
  # emissions_torch <- torch::torch_tensor(emissions)
  # 
  # results_numeric_torch <- decoder$decode(as.numeric(emissions_torch$storage()$data_ptr()), T, N)
  # results_chr_torch <- decoder$decode(emissions_torch$storage()$data_ptr(), T, N)
  # results_torch <- decoder$decode(emissions_torch, T, N)
  # expect_equal(results, results_numeric_torch)
  # expect_equal(results, results_chr_torch)
  # expect_equal(results, results_torch)
  
  scores <- purrr::map_dbl(results, "score")
  tokens <- purrr::map(results, "tokens")
  for(i in seq_along(scores)) {
    prediction = c()
    for(idx in tokens[[i]]) {
      if(idx < 0) break
      prediction = c(prediction, token_dict$get_entry(idx))
    }
    prediction = paste(prediction, collapse = "")
  }
  
  expect_equal(length(scores), 16)
  hyp_score_target <- c(-284.0998, -284.108, -284.119, -284.127, -284.296)
  for(i in seq_along(hyp_score_target)) {
    expect_equal(scores[i], hyp_score_target[i], tolerance = 1e-3) 
  }
  
  # n_hypothesis
  expect_equal(decoder$n_hypothesis(), 16)
  expect_equal(names(decoder$get_all_final_hypothesis()), c("score", "emittingModelScore", "lmScore", "words", "tokens"))
  expect_equal(decoder$n_decoded_frames_in_buffer(), 237)
  expect_no_error(best_hypo <- decoder$get_best_hypothesis())
  expect_equal(best_hypo$score, hyp_score_target[1], tolerance = 1e-3)
  expect_equal(length(best_hypo$words[[1]]), 237)
  decoder$prune(1)
  expect_equal(decoder$n_decoded_frames_in_buffer(), 4)
  expect_no_error(best_hypo_pruned <- decoder$get_best_hypothesis())
  expect_equal(length(best_hypo_pruned$words[[1]]), 4)
})

