#' Decoder
#' 
#' @export
#' @rdname Decoder
#' 
#' @examples
#' 
#' library(flashlighttext)
#' 
#' decoder <- Decoder$new()
Decoder <- R6::R6Class(
  "Decoder",
  public = list(
    #' @return invisible(NULL)
    initialize = function() {},
    #' @return invisible(NULL)
    decode_begin = function() {},
    #' @param emissions a emissions 
    #' @param T a T 
    #' @param N a N 
    #' @return invisible(NULL)
    decode_step = function(emissions, T, N) {},
    #' @return invisible(NULL)
    decode_end = function() {},
    #' @param emissions a emissions 
    #' @param T a T 
    #' @param N a N 
    #' @return invisible(NULL)
    decode = function(emissions, T, N) {
      self$decode_begin()
      self$decode_step(emissions, T, N)
      self$decode_end()
      return(self$get_all_final_hypothesis())
    },
    #' @param lookBack a lookBack
    #' @return invisible(NULL)
    prune = function(lookBack = 0) {},
    #' @return invisible(NULL)
    n_decoded_frames_in_buffer = function() {},
    #' @param lookBack a lookBack
    #' @return invisible(NULL)
    get_best_hypothesis = function(lookBack = 0) {},
    #' @return invisible(NULL)
    get_all_final_hypothesis = function() {}
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