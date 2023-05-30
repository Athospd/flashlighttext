#' LexiconSeq2SeqDecoderOptions
#'
#' @export
#' @rdname LexiconSeq2SeqDecoderOptions
LexiconSeq2SeqDecoderOptions <- R6::R6Class(
  "LexiconSeq2SeqDecoderOptions",
  inherit = Decoder,
  public = list(
    #' @param beam_size an integer. Maximum number of hypothesis we hold after each step
    #' @param beam_size_token an integer. Maximum number of tokens we consider at each step
    #' @param beam_threshold a numeric. Threshold to prune hypothesis
    #' @param lm_weight a numeric. Weight of lm
    #' @param word_score a numeric. Word insertion score
    #' @param eos_score a numeric. Score for inserting an EOS
    #' @param log_add a logical. If or not use logadd when merging hypothesis
    #' @returns LexiconSeq2SeqDecoderOptions
    initialize = function(
    beam_size,
    beam_size_token,
    beam_threshold,
    lm_weight,
    word_score,
    eos_score,
    log_add
    ) {
      private$beam_size_ = beam_size
      private$beam_size_token_ = beam_size_token
      private$beam_threshold_ = beam_threshold
      private$lm_weight_ = lm_weight
      private$word_score_ = word_score
      private$eos_score_ = eos_score
      private$log_add_ = log_add
      private$ptr_ <- cpp_LexiconSeq2SeqDecoderOptions_constructor(
        beam_size,
        beam_size_token,
        beam_threshold,
        lm_weight,
        word_score,
        eos_score,
        log_add
      )
    }
  ),
  
  active = list(
    #' @field beam_size Maximum number of hypothesis we hold after each step
    #' @field beam_size_token Maximum number of tokens we consider at each step
    #' @field beam_threshold Threshold to prune hypothesis
    #' @field lm_weight Weight of lm
    #' @field word_score Word insertion score
    #' @field eos_score Score for inserting an EOS
    #' @field log_add If or not use logadd when merging hypothesis
    #' @field ptr set and get the pointer to a LexiconSeq2SeqDecoderOptions instance.
    ptr = function(new_ptr) {
      if(!missing(new_ptr)) private$ptr_ <- new_ptr
      private$ptr_
    },
    beam_size = function(value) {
      if(!missing(value)) {
        private$beam_size_ <- value
        cpp_LexiconSeq2SeqDecoderOptions_set_beamSize(self$ptr, value)
      } else {
        cpp_LexiconSeq2SeqDecoderOptions_get_beamSize(self$ptr)
      }
    },
    beam_size_token = function(value) {
      if(!missing(value)) {
        private$beam_size_token_ <- value
        cpp_LexiconSeq2SeqDecoderOptions_set_beamSizeToken(self$ptr, value)
      } else {
        cpp_LexiconSeq2SeqDecoderOptions_get_beamSizeToken(self$ptr)
      }
    },
    beam_threshold = function(value) {
      if(!missing(value)) {
        private$beam_threshold_ <- value
        cpp_LexiconSeq2SeqDecoderOptions_set_beamThreshold(self$ptr, value)
      } else {
        cpp_LexiconSeq2SeqDecoderOptions_get_beamThreshold(self$ptr)
      }
    },
    lm_weight = function(value) {
      if(!missing(value)) {
        private$lm_weight_ <- value
        cpp_LexiconSeq2SeqDecoderOptions_set_lmWeight(self$ptr, value)
      } else {
        cpp_LexiconSeq2SeqDecoderOptions_get_lmWeight(self$ptr)
      }
    },
    word_score = function(value) {
      if(!missing(value)) {
        private$word_score_ <- value
        cpp_LexiconSeq2SeqDecoderOptions_set_wordScore(self$ptr, value)
      } else {
        cpp_LexiconSeq2SeqDecoderOptions_get_wordScore(self$ptr)
      }
    },
    eos_score = function(value) {
      if(!missing(value)) {
        private$eos_score_ <- value
        cpp_LexiconSeq2SeqDecoderOptions_set_eosScore(self$ptr, value)
      } else {
        cpp_LexiconSeq2SeqDecoderOptions_get_eosScore(self$ptr)
      }
    },
    log_add = function(value) {
      if(!missing(value)) {
        private$log_add_ <- value
        cpp_LexiconSeq2SeqDecoderOptions_set_logAdd(self$ptr, value)
      } else {
        cpp_LexiconSeq2SeqDecoderOptions_get_logAdd(self$ptr)
      }
    }
  ),
  
  private = list(
    ptr_ = NULL,
    beam_size_ = NULL,
    beam_size_token_ = NULL,
    beam_threshold_ = NULL,
    lm_weight_ = NULL,
    word_score_ = NULL,
    eos_score_ = NULL,
    log_add_ = NULL
  )
)

#' LexiconSeq2SeqDecoder
#' 
#' Decoder implements a beam seach decoder that finds the token transcription.
#' W maximizing:
#' 
#' AM(W) + lmWeight_ * log(P_{lm}(W)) + eosScore_ * |W_last == EOS|
#' 
#' where P_{lm}(W) is the language model score. The transcription W is 
#' constrained by a lexicon. The language model may operate at word-level 
#' (isLmToken = FALSE) or token-level (isLmToken = TRUE).
#'
#' @export
#' @rdname LexiconSeq2SeqDecoder
LexiconSeq2SeqDecoder <- R6::R6Class(
  "LexiconSeq2SeqDecoder",
  inherit = Decoder,
  public = list(
    
    #' @param options a LexiconSeq2SeqDecoderOptions instance. 
    #' @param trie a Trie instance 
    #' @param lm a LM instance
    #' @param eos an integer. The index representing the EOS.
    #' @param emitting_model_update_func an emittingModelUpdateFunc instance
    #' @param max_output_length an integer. The maximum output length.
    #' @param is_lm_token a is_lm_token 
    #' @return LexiconSeq2SeqDecoder
    initialize = function(
    options, 
    trie, 
    lm, 
    eos, 
    emitting_model_update_func,
    max_output_length, 
    is_lm_token
    ) {
      private$options_ <- options
      private$trie_ <- trie
      private$lm_ <- lm
      private$eos_ <- eos
      private$emitting_model_update_func_ <- emitting_model_update_func
      private$max_output_length_ <- max_output_length
      private$is_lm_token_ <- is_lm_token
      private$ptr_ <- cpp_LexiconSeq2SeqDecoder_constructor(
        options$ptr, 
        trie$ptr, 
        lm$ptr, 
        eos, 
        emitting_model_update_func$ptr,
        max_output_length,
        is_lm_token
      )
    },
    
    #' @return int
    n_hypothesis = function() {
      cpp_LexiconSeq2SeqDecoder_nHypothesis(self$ptr)
    }
  ),
  
  private = list(
    options_ = NULL,
    trie_ = NULL,
    lm_ = NULL,
    eos_ = NULL,
    emitting_model_update_func_ = NULL,
    max_output_length_ = NULL,
    is_lm_token_ = NULL
  )
)


