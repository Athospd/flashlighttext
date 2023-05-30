#' LexiconDecoderOptions
#'
#' @export
#' @rdname LexiconDecoderOptions
LexiconDecoderOptions <- R6::R6Class(
  "LexiconDecoderOptions",
  public = list(
    #' @param beam_size Maximum number of hypothesis we hold after each step
    #' @param beam_size_token Maximum number of tokens we consider at each step
    #' @param beam_threshold Threshold to prune hypothesis
    #' @param lm_weight Weight of lm
    #' @param word_score Word insertion score
    #' @param unk_score Unknown word insertion score
    #' @param sil_score Silence insertion score
    #' @param log_add If or not use logadd when merging hypothesis
    #' @param criterion_type a CriterionType: "CTC" or "ASG" (see [CriterionTypes])
    #' @examples
    #' opts <- LexiconDecoderOptions$new(
    #'   beam_size = 2500,
    #'   beam_size_token = 25000,
    #'   beam_threshold = 100.0,
    #'   lm_weight = 2.0,
    #'   word_score = 2.0,
    #'   unk_score = -Inf,
    #'   sil_score = -1,
    #'   log_add = FALSE,
    #'   criterion_type = CriterionTypes$ASG
    #' )
    #' 
    #' @returns LexiconDecoderOptions
    initialize = function(
    beam_size,
    beam_size_token,
    beam_threshold,
    lm_weight,
    word_score,
    unk_score,
    sil_score,
    log_add,
    criterion_type
    ) {
      private$beam_size_ = beam_size
      private$beam_size_token_ = beam_size_token
      private$beam_threshold_ = beam_threshold
      private$lm_weight_ = lm_weight
      private$word_score_ = word_score
      private$unk_score_ = unk_score
      private$sil_score_ = sil_score
      private$log_add_ = log_add
      private$criterion_type_ = criterion_type
      private$ptr_ <- cpp_LexiconDecoderOptions_constructor(
        beam_size,
        beam_size_token,
        beam_threshold,
        lm_weight,
        word_score,
        unk_score,
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
    #' @field word_score Word insertion score
    #' @field unk_score Unknown word insertion score
    #' @field sil_score Silence insertion score
    #' @field log_add If or not use logadd when merging hypothesis
    #' @field criterion_type a CriterionType: "CTC" or "ASG" (see [CriterionTypes])
    #' @field ptr set and get the pointer to a LexiconDecoderOptions instance.
    ptr = function(new_ptr) {
      if(!missing(new_ptr)) private$ptr_ <- new_ptr
      private$ptr_
    },
    beam_size = function(value) {
      if(!missing(value)) {
        private$beam_size_ <- value
        cpp_LexiconDecoderOptions_set_beamSize(self$ptr, value)
      } else {
        cpp_LexiconDecoderOptions_get_beamSize(self$ptr)
      }
    },
    beam_size_token = function(value) {
      if(!missing(value)) {
        private$beam_size_token_ <- value
        cpp_LexiconDecoderOptions_set_beamSizeToken(self$ptr, value)
      } else {
        cpp_LexiconDecoderOptions_get_beamSizeToken(self$ptr)
      }
    },
    beam_threshold = function(value) {
      if(!missing(value)) {
        private$beam_threshold_ <- value
        cpp_LexiconDecoderOptions_set_beamThreshold(self$ptr, value)
      } else {
        cpp_LexiconDecoderOptions_get_beamThreshold(self$ptr)
      }
    },
    lm_weight = function(value) {
      if(!missing(value)) {
        private$lm_weight_ <- value
        cpp_LexiconDecoderOptions_set_lmWeight(self$ptr, value)
      } else {
        cpp_LexiconDecoderOptions_get_lmWeight(self$ptr)
      }
    },
    word_score = function(value) {
      if(!missing(value)) {
        private$word_score_ <- value
        cpp_LexiconDecoderOptions_set_wordScore(self$ptr, value)
      } else {
        cpp_LexiconDecoderOptions_get_wordScore(self$ptr)
      }
    },
    unk_score = function(value) {
      if(!missing(value)) {
        private$unk_score_ <- value
        cpp_LexiconDecoderOptions_set_unkScore(self$ptr, value)
      } else {
        cpp_LexiconDecoderOptions_get_unkScore(self$ptr)
      }
    },
    sil_score = function(value) {
      if(!missing(value)) {
        private$sil_score_ <- value
        cpp_LexiconDecoderOptions_set_silScore(self$ptr, value)
      } else {
        cpp_LexiconDecoderOptions_get_silScore(self$ptr)
      }
    },
    log_add = function(value) {
      if(!missing(value)) {
        private$log_add_ <- value
        cpp_LexiconDecoderOptions_set_logAdd(self$ptr, value)
      } else {
        cpp_LexiconDecoderOptions_get_logAdd(self$ptr)
      }
    },
    criterion_type = function(value) {
      if(!missing(value)) {
        private$criterion_type_ <- value
        cpp_LexiconDecoderOptions_set_CriterionType(self$ptr, value)
      } else {
        cpp_LexiconDecoderOptions_get_CriterionType(self$ptr)
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
    unk_score_ = NULL,
    sil_score_ = NULL,
    log_add_ = NULL,
    criterion_type_ = NULL
  )
)

#' LexiconDecoder
#' 
#' Decoder implements a beam seach decoder that finds the word transcription
#' W maximizing:
#' 
#' AM(W) + lmWeight_ * log(P_{lm}(W)) + wordScore_ * |W_known| + unkScore_ * 
#' |W_unknown| + silScore_ * |{i| pi_i = <sil>}|
#' 
#' where P_{lm}(W) is the language model score, pi_i is the value for the i-th
#' frame in the path leading to W and AM(W) is the (unnormalized) emitting model
#' score of the transcription W. Note that the lexicon is used to limit the
#' search space and all candidate words are generated from it if unkScore is
#' -inf, otherwise <UNK> will be generated for OOVs.
#'
#' @export
#' @rdname LexiconDecoder
LexiconDecoder <- R6::R6Class(
  "LexiconDecoder",
  inherit = Decoder,
  public = list(
    
    #' @param options a LexiconDecoderOptions instance 
    #' @param trie a Trie instance. Lexicon trie to restrict beam-search decoder
    #' @param lm a LM instance (e.g. KenLM or ZeroLM) 
    #' @param sil_token_idx a character. The silence token index 
    #' @param blank_token_idx a character. The blank token index (for CTC)
    #' @param unk_token_idx a character. The unkown token index 
    #' @param transitions a tensor. Matrix of transitions (for ASG criterion)
    #' @param is_lm_token a is_lm_token 
    #' @return LexiconDecoder
    initialize = function(
      options, 
      trie, 
      lm, 
      sil_token_idx, 
      blank_token_idx, 
      unk_token_idx, 
      transitions, 
      is_lm_token
    ) {
      private$options_ <- options
      private$trie_ <- trie
      private$lm_ <- lm
      private$sil_token_idx_ <- sil_token_idx
      private$blank_token_idx_ <- blank_token_idx
      private$unk_token_idx_ <- unk_token_idx
      private$transitions_ <- transitions
      private$is_lm_token_ <- is_lm_token
      private$ptr_ <- cpp_LexiconDecoder_constructor(
        options$ptr, 
        trie$ptr, 
        lm$ptr, 
        sil_token_idx, 
        blank_token_idx, 
        unk_token_idx, 
        transitions, 
        is_lm_token
      )
    },
    
    #' @return an integer
    n_hypothesis = function() {
      cpp_LexiconDecoder_nHypothesis(self$ptr)
    }
  ),
  
  private = list(
    options_ = NULL,
    trie_ = NULL,
    lm_ = NULL,
    sil_token_idx_ = NULL,
    blank_token_idx_ = NULL,
    unk_token_idx_ = NULL,
    transitions_ = NULL,
    is_lm_token_ = NULL,
    candidates_ = NULL,
    candidatePtrs_ = NULL,
    candidatesBestScore_ = NULL,
    hyp_ = NULL,
    nDecodedFrames_ = NULL,
    nPrunedFrames_ = NULL
  )
)


