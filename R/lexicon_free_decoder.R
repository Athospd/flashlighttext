#' LexiconFreeDecoderOptions
#'
#' @rdname LexiconFreeDecoderOptions
#' @export
LexiconFreeDecoderOptions <- R6::R6Class(
  "LexiconFreeDecoderOptions",
  public = list(
    #' @param beam_size Maximum number of hypothesis we hold after each step
    #' @param beam_size_token Maximum number of tokens we consider at each step
    #' @param beam_threshold Threshold to prune hypothesis
    #' @param lm_weight Weight of lm
    #' @param sil_score Silence insertion score
    #' @param log_add If or not use logadd when merging hypothesis
    #' @param criterion_type a CriterionType: "CTC" or "ASG" (see [CriterionTypes])
    #' @returns LexiconFreeDecoderOptions
    initialize = function(
      beam_size,
      beam_size_token,
      beam_threshold,
      lm_weight,
      sil_score,
      log_add,
      criterion_type
    ) {
      private$beam_size_ = beam_size
      private$beam_size_token_ = beam_size_token
      private$beam_threshold_ = beam_threshold
      private$lm_weight_ = lm_weight
      private$sil_score_ = sil_score
      private$log_add_ = log_add
      private$criterion_type_ = criterion_type
      private$ptr_ <- cpp_LexiconFreeDecoderOptions_constructor(
        beam_size,
        beam_size_token,
        beam_threshold,
        lm_weight,
        sil_score,
        log_add,
        criterion_type
      )
    }
  ),
  
  active = list(
    #' @field beam_size Maximum number of hypothesis we hold after each step
    #' @field beam_size_token Maximum number of tokens we consider at each step
    #' @field beam_threshold Threshold to prune hypothesis
    #' @field lm_weight Weight of lm
    #' @field sil_score Silence insertion score
    #' @field log_add If or not use logadd when merging hypothesis
    #' @field criterion_type a CriterionType: "CTC" or "ASG" (see [CriterionTypes])
    #' @field ptr set and get the pointer to a LexiconFreeDecoderOptions instance.
    ptr = function(new_ptr) {
      if(!missing(new_ptr)) private$ptr_ <- new_ptr
      private$ptr_
    },
    beam_size = function(value) {
      if(!missing(value)) {
        private$beam_size_ <- value
        cpp_LexiconFreeDecoderOptions_set_beamSize(self$ptr, value)
      } else {
        cpp_LexiconFreeDecoderOptions_get_beamSize(self$ptr)
      }
    },
    beam_size_token = function(value) {
      if(!missing(value)) {
        private$beam_size_token_ <- value
        cpp_LexiconFreeDecoderOptions_set_beamSizeToken(self$ptr, value)
      } else {
        cpp_LexiconFreeDecoderOptions_get_beamSizeToken(self$ptr)
      }
    },
    beam_threshold = function(value) {
      if(!missing(value)) {
        private$beam_threshold_ <- value
        cpp_LexiconFreeDecoderOptions_set_beamThreshold(self$ptr, value)
      } else {
        cpp_LexiconFreeDecoderOptions_get_beamThreshold(self$ptr)
      }
    },
    lm_weight = function(value) {
      if(!missing(value)) {
        private$lm_weight_ <- value
        cpp_LexiconFreeDecoderOptions_set_lmWeight(self$ptr, value)
      } else {
        cpp_LexiconFreeDecoderOptions_get_lmWeight(self$ptr)
      }
    },
    sil_score = function(value) {
      if(!missing(value)) {
        private$sil_score_ <- value
        cpp_LexiconFreeDecoderOptions_set_silScore(self$ptr, value)
      } else {
        cpp_LexiconFreeDecoderOptions_get_silScore(self$ptr)
      }
    },
    log_add = function(value) {
      if(!missing(value)) {
        private$log_add_ <- value
        cpp_LexiconFreeDecoderOptions_set_logAdd(self$ptr, value)
      } else {
        cpp_LexiconFreeDecoderOptions_get_logAdd(self$ptr)
      }
    },
    criterion_type = function(value) {
      if(!missing(value)) {
        private$criterion_type_ <- value
        cpp_LexiconFreeDecoderOptions_set_CriterionType(self$ptr, value)
      } else {
        cpp_LexiconFreeDecoderOptions_get_CriterionType(self$ptr)
      }
    }
    
  ),
  
  private = list(
    ptr_ = NULL,
    beam_size_ = NULL,
    beam_size_token_ = NULL,
    beam_threshold_ = NULL,
    lm_weight_ = NULL,
    sil_score_ = NULL,
    log_add_ = NULL,
    criterion_type_ = NULL
  )
)



#' LexiconFreeDecoder
#'
#' @export
#' @rdname LexiconFreeDecoder
LexiconFreeDecoder <- R6::R6Class(
  "LexiconFreeDecoder",
  inherit = Decoder,
  public = list(
    
    #' @param options a options 
    #' @param lm a lm 
    #' @param sil_token_idx a sil_token_idx 
    #' @param blank_token_idx a blank_token_idx 
    #' @param transitions a transitions 
    #' @param is_lm_token a is_lm_token 
    #' @return LexiconFreeDecoder
    initialize = function(
    options, 
    lm, 
    sil_token_idx, 
    blank_token_idx, 
    transitions
    ) {
      private$options_ <- options
      private$lm_ <- lm
      private$sil_token_idx_ <- sil_token_idx
      private$blank_token_idx_ <- blank_token_idx
      private$transitions_ <- transitions
      private$ptr_ <- cpp_LexiconFreeDecoder_constructor(
        options$ptr, 
        lm$ptr, 
        sil_token_idx, 
        blank_token_idx, 
        transitions
      )
    },
    
    #' @return int
    n_hypothesis = function() {
      cpp_LexiconFreeDecoder_nHypothesis(self$ptr)
    },
    #' @return a externalpointer
    get_lm_ptr = function() {
      not_implemented_error("getLMPtr method not implemented yet.")
      # cpp_LexiconFreeDecoder_getLMPtr(self$ptr)
    },
    #' @return list of DecodeResult
    get_sil_idx = function() {
      cpp_LexiconFreeDecoder_getSilIdx(self$ptr)
    },
    #' @return list of DecodeResult
    get_blank_idx = function() {
      cpp_LexiconFreeDecoder_getBlankIdx(self$ptr)
    },
    #' @return list of DecodeResult
    get_options = function() {
      cpp_LexiconFreeDecoder_getOptions(self$ptr)
    },
    #' @return list of DecodeResult
    get_transitions = function() {
      cpp_LexiconFreeDecoder_getTransitions(self$ptr)
    }
  ),
  
  private = list(
    options_ = NULL,
    lm_ = NULL,
    sil_token_idx_ = NULL,
    blank_token_idx_ = NULL,
    transitions_ = NULL,
    candidates_ = NULL,
    candidatePtrs_ = NULL,
    candidatesBestScore_ = NULL,
    hyp_ = NULL,
    nDecodedFrames_ = NULL,
    nPrunedFrames_ = NULL
  )
)
