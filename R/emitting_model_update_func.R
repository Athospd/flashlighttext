# https://github.com/flashlight/text/blob/7cba9a1351eba52727bc2948a66c62cb75ca60d1/flashlight/lib/text/decoder/Utils.h
#' @export
EmittingModelUpdateFunc <- R6::R6Class(
  "EmittingModelUpdateFunc",
  public = list(
    initialize = function() {
      stop("to do (parameters?)")
      private$ptr_ <- cpp_EmittingModelUpdateFunc_constructor()
    }
  ),
  
  active = list(
    #' @field ptr set and get the pointer to a LexiconFreeSeq2SeqDecoderOptions instance.
    ptr = function(new_ptr) {
      if(!missing(new_ptr)) private$ptr_ <- new_ptr
      private$ptr_
    }
  ),
  
  private = list(
    ptr_ = NULL
  )
)