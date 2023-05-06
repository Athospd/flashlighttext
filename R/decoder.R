#' Decoder
#' @export
#' @rdname Decoder
#'
#' @examples
#'
#' library(flashlighttext)
#'
#' decoder <- Decoder$new()
# Decoder <- R6::R6Class(
#   "Decoder",
#   public = list(
#     initialize = function() {},
#     decodeBegin = function() {},
#     decodeStep = function(emissions, T, N) {},
#     decodeEnd = function() {},
#     decode = function(emissions, T, N) {
#       self$decodeBegin()
#       self$decodeStep(emissions, T, N)
#       self$decodeEnd()
#       return(self$getAllFinalHypothesis())
#     },
#     prune = function(lookBack = 0) {},
#     nDecodedFramesInBuffer = function() {},
#     getBestHypothesis = function(lookBack = 0) {},
#     getAllFinalHypothesis = function() {}
#   ),
#   
#   active = list(
#     ptr = function(new_ptr) {
#       if(!missing(new_ptr)) {
#         private$ptr_ <- new_ptr
#       }
#       
#       if(is_null_externalptr(private$ptr_)) 
#         private$ptr_ <- cpp_Decoder_create()
#       
#       private$ptr_
#     },
#     
#     filename = function() {
#       private$filename_
#     },
#     
#     tokens = function() {
#       private$tokens_
#     }
#   ),
#   
#   private = list(
#     ptr_ = NULL
#   )
# )
