#' LexiconFreeSeq2SeqDecoderOptions
#'
#' @rdname LexiconFreeSeq2SeqDecoderOptions
#' @export
LexiconFreeSeq2SeqDecoderOptions <- R6::R6Class(
  "LexiconFreeSeq2SeqDecoderOptions",
  inherit = Decoder,
  public = list(
    #' @param beam_size Maximum number of hypothesis we hold after each step
    #' @param beam_size_token Maximum number of tokens we consider at each step
    #' @param beam_threshold Threshold to prune hypothesis
    #' @param lm_weight Weight of lm
    #' @param eos_score Score for inserting an EOS
    #' @param log_add If or not use logadd when merging hypothesis
    #' @returns LexiconFreeSeq2SeqDecoderOptions
    initialize = function(
      beam_size,
      beam_size_token,
      beam_threshold,
      lm_weight,
      eos_score,
      log_add
    ) {
      private$beam_size_ = beam_size
      private$beam_size_token_ = beam_size_token
      private$beam_threshold_ = beam_threshold
      private$lm_weight_ = lm_weight
      private$eos_score_ = eos_score
      private$log_add_ = log_add
      private$ptr_ <- cpp_LexiconFreeSeq2SeqDecoderOptions_constructor(
        beam_size,
        beam_size_token,
        beam_threshold,
        lm_weight,
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
    #' @field eos_score Silence insertion score
    #' @field log_add If or not use logadd when merging hypothesis
    #' @field ptr set and get the pointer to a LexiconFreeSeq2SeqDecoderOptions instance.
    ptr = function(new_ptr) {
      if(!missing(new_ptr)) private$ptr_ <- new_ptr
      private$ptr_
    },
    beam_size = function(value) {
      if(!missing(value)) {
        private$beam_size_ <- value
        cpp_LexiconFreeSeq2SeqDecoderOptions_set_beamSize(self$ptr, value)
      } else {
        cpp_LexiconFreeSeq2SeqDecoderOptions_get_beamSize(self$ptr)
      }
    },
    beam_size_token = function(value) {
      if(!missing(value)) {
        private$beam_size_token_ <- value
        cpp_LexiconFreeSeq2SeqDecoderOptions_set_beamSizeToken(self$ptr, value)
      } else {
        cpp_LexiconFreeSeq2SeqDecoderOptions_get_beamSizeToken(self$ptr)
      }
    },
    beam_threshold = function(value) {
      if(!missing(value)) {
        private$beam_threshold_ <- value
        cpp_LexiconFreeSeq2SeqDecoderOptions_set_beamThreshold(self$ptr, value)
      } else {
        cpp_LexiconFreeSeq2SeqDecoderOptions_get_beamThreshold(self$ptr)
      }
    },
    lm_weight = function(value) {
      if(!missing(value)) {
        private$lm_weight_ <- value
        cpp_LexiconFreeSeq2SeqDecoderOptions_set_lmWeight(self$ptr, value)
      } else {
        cpp_LexiconFreeSeq2SeqDecoderOptions_get_lmWeight(self$ptr)
      }
    },
    eos_score = function(value) {
      if(!missing(value)) {
        private$eos_score_ <- value
        cpp_LexiconFreeSeq2SeqDecoderOptions_set_silScore(self$ptr, value)
      } else {
        cpp_LexiconFreeSeq2SeqDecoderOptions_get_silScore(self$ptr)
      }
    },
    log_add = function(value) {
      if(!missing(value)) {
        private$log_add_ <- value
        cpp_LexiconFreeSeq2SeqDecoderOptions_set_logAdd(self$ptr, value)
      } else {
        cpp_LexiconFreeSeq2SeqDecoderOptions_get_logAdd(self$ptr)
      }
    }
  ),
  
  private = list(
    ptr_ = NULL,
    beam_size_ = NULL,
    beam_size_token_ = NULL,
    beam_threshold_ = NULL,
    lm_weight_ = NULL,
    eos_score_ = NULL,
    log_add_ = NULL
  )
)



#' LexiconFreeSeq2SeqDecoder
#'
#' @export
#' @rdname LexiconFreeSeq2SeqDecoder
LexiconFreeSeq2SeqDecoder <- R6::R6Class(
  "LexiconFreeSeq2SeqDecoder",
  inherit = Decoder,
  public = list(
    
    #' @param options an options 
    #' @param lm a lm 
    #' @param eos_token_idx an eos_token_idx 
    #' @param emitting_model_update_func an emitting_model_update_func 
    #' @param max_output_length a max_output_length 
    #' @return LexiconFreeSeq2SeqDecoder
    initialize = function(
      options, 
      lm, 
      eos_token_idx, 
      emitting_model_update_func, 
      max_output_length
    ) {
      private$options_ <- options
      private$lm_ <- lm
      private$eos_token_idx_ <- eos_token_idx
      private$emitting_model_update_func_ <- emitting_model_update_func
      private$max_output_length_ <- max_output_length
      private$ptr_ <- cpp_LexiconFreeSeq2SeqDecoder_constructor(
        options$ptr, 
        lm$ptr, 
        eos_token_idx, 
        emitting_model_update_func$ptr, 
        max_output_length
      )
    },
    
    #' @return int
    n_hypothesis = function() {
      cpp_LexiconFreeSeq2SeqDecoder_nHypothesis(self$ptr)
    }
  ),
  
  private = list(
    options_ = NULL,
    lm_ = NULL,
    eos_token_idx_ = NULL,
    emitting_model_update_func_ = NULL,
    raw_y_ = NULL,
    raw_beam_idx_ = NULL,
    raw_prev_states_ = NULL,
    max_output_length_ = NULL,
    candidates_ = NULL,
    candidatePtrs_ = NULL,
    candidatesBestScore_ = NULL,
    hyp_ = NULL
  )
)
