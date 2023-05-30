#' Decoder
#' 
#' @export
#' @rdname Decoder
Decoder <- R6::R6Class(
  "Decoder",
  public = list(
    
    #' @description
    #' Decoder is a base class and cannot be initialized directly. It is inherited
    #' by other LM classes shuch as KenLM and ZeroLM.
    #' @returns invisible(NULL)
    initialize = function() {
      stop("Decoder is a base class and cannot be initialized.")
    },
    
    #' @param emissions the emissions. Dimension (Batch=1, Time, Ntokens)
    #' @param T an integer. Number of tokens (Ntokens).
    #' @param N an integer. Number of timesteps (Time).
    #' @return invisible(NULL)
    decode = function(emissions, T, N) {
      if(inherits(emissions, "torch_tensor")) {
        emissions <- as.numeric(emissions$storage()$data_ptr())
        result <- cpp_Decoder_decode_numeric_ptr(self$ptr, emissions, T, N)
      }
      
      if(inherits(emissions, "character") & length(emissions) == 1) {
        emissions <- as.numeric(emissions)
        result <- cpp_Decoder_decode_numeric_ptr(self$ptr, emissions, T, N)
      }
      
      if(inherits(emissions, "numeric") & length(emissions) == 1) 
        result <- cpp_Decoder_decode_numeric_ptr(self$ptr, emissions, T, N)
      
      if(inherits(emissions, "numeric") & length(emissions) > 1) 
        result <- cpp_Decoder_decode_numeric_vector(self$ptr, emissions, T, N)
      
      return(purrr::transpose(result))
    },
    
    #' @description
    #' Prune the hypothesis space
    #' @param lookBack an integer. Number of frames to look back.
    #' @return invisible(NULL)
    prune = function(lookBack = 0) {
      cpp_Decoder_prune(self$ptr, lookBack)
    },
    
    #' @return an integer
    n_decoded_frames_in_buffer = function() {
      cpp_Decoder_nDecodedFramesInBuffer(self$ptr)
    },
    
    #' @param lookBack an integer. Number of frames to look back.
    #' @return a DecodeResult instance
    get_best_hypothesis = function(lookBack = 0) {
      cpp_Decoder_getBestHypothesis(self$ptr, lookBack)
    },
    
    #' @return list of DecodeResult instances
    get_all_final_hypothesis = function() {
      cpp_Decoder_getAllFinalHypothesis(self$ptr)
    }
  ),

  active = list(
    #' @field ptr set and get the pointer to a Decoder instance.
    ptr = function(new_ptr) {
      if(!missing(new_ptr)) private$ptr_ <- new_ptr
      private$ptr_
    }
  ),

  private = list(
    ptr_ = NULL
  )
)

#' CriterionTypes
#'
#' A enum (list) of criterion types.
#'
#' @format ## `CriterionTypes`
#' A list with 3 items:
#' \describe{
#'   \item{ASG}{string "ASG"}
#'   \item{CTC}{string "CTC"}
#'   \item{S2S}{string "S2S"}
#' }
"CriterionTypes"