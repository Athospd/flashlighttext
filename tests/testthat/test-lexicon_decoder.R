sys_file <- function(file) system.file(file, package = "flashlighttext")
read_bin <- function(file, type, size) readBin(sys_file(file), size = size, type, n = 10000)
tkn_to_idx <- function(spelling, token_dict, maxReps = 0){
  result <- c()
  for(token in spelling) {
    result <- c(result, token_dict$get_index(token))
  }
  return(pack_replabels(result, token_dict, maxReps))
}
  
test_that("lexicon_decoder", {
  # emissions ---------------------------------------------------------------
 
  c(T, N) %<-% read_bin("TN.bin", "integer", size = 4) 
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
  trie <- Trie$new(token_dict$index_size(), separator_idx) 
  start_state <- lm$start(FALSE)
  for(word in names(lexicon)) {
    spellings <- if(word != "<unk>") lexicon[[word]] else list()
    usr_idx <- word_dict$get_index(word)
    score <- lm$score(start_state, usr_idx)[[2]]
    for(spelling in spellings) {
      spelling_idxs = tkn_to_idx(spelling, token_dict, 1)
      trie$insert(spelling_idxs, usr_idx, score)
    }
  }
  trie$smear(SmearingModes$MAX)
  
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
    is_token_lm = FALSE
  )
  
  # run decoding
  results <- decoder$decode(emissions, T, N)
  
  print(f("Decoding complete, obtained {length(results)} results"))
  print("Showing top 5 results:")
  for(i in seq_along(results$score)) {
    prediction = c()
    for(idx in results$tokens[[i]]) {
      if(idx < 0) break
      prediction = c(prediction, token_dict$get_entry(idx))
    }
    prediction = paste(prediction, collapse = "")
    # print(f("score={results$score[[i]]} emittingModelScore={results$emittingModelScore[[i]]} lmScore={results$lmScore[[i]]} prediction='{prediction}'"))
  }
      
  expect_equal(length(results$score), 16)
  hyp_score_target <- c(-284.0998, -284.108, -284.119, -284.127, -284.296)
  for(i in seq_along(hyp_score_target)) {
    # print(c(results$score[[i]], hyp_score_target[i]))
    expect_equal(results$score[[i]], hyp_score_target[i], tolerance = 1e-3) 
  }
})