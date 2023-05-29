test_that("lexicon_free_decoder", {
  T = 3
  N = 4
  emissions = seq.int(T*N) - (T*N)/2 - 1
  expect_equal(length(emissions), T*N)
  
  beam_size = 2
  eos_idx = 4
  max_output_length = 3
  
  # timestep --> autoregressive scores
  model_score_mapping = list(
    c(0.1, 0.1, 0.5, 0.1),
    c(0.5, 0.2, 0.1, 0.0),
    c(0.1, 0.5, 0.1, 0.1)
  )
  expect_equal(length(model_score_mapping), T)
  
  options <- LexiconFreeSeq2SeqDecoderOptions$new(
    beam_size = beam_size,
    beam_size_token = 4,
    beam_threshold = 1000,
    lm_weight = 0,
    eos_score = 0,
    log_add = TRUE
  )
  
  # expect_no_error(decoder <- LexiconFreeSeq2SeqDecoder$new(
  #   options = options,
  #   lm = ZeroLM$new(),
  #   eos_token_idx = eos_idx,
  #   emitting_model_update_func = update_func,
  #   max_output_length = max_output_length
  # ))
  # 
  # decoder$decode_step(emissions, T, N)
  # hyps <- decoder$get_all_final_hypothesis()
})
