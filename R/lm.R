#' LM
#' 
#' @export
LM <- R6::R6Class(
  "LM",
  public = list(
    #' @return NULL
    initialize = function() {},
    
    #' @param start_with_nothing A boolean indicating whether or not to start
    #' the sentence with a sil token.
    #' @return LMState
    start = function(start_with_nothing = FALSE) {
      stop("start method must be implemented by subclass")
    },
    
    #' @param state a state
    #' @param usrTokenIdx a usrTokenIdx
    #' @return list(LMState, numeric)
    score = function(state, usrTokenIdx) {
      stop("score method must be implemented by subclass")
    },
    
    #' @param state a state
    #' @return list(LMState, numeric)
    finish = function(state) {
      stop("finish method must be implemented by subclass")
    }
  ),
  
  active = list(
    #' @field 
    #' ptr get or set a pointer to a (*)LMWrapper.
    ptr = function(new_ptr) {
      if(!missing(new_ptr)) private$ptr_ <- new_ptr
      private$ptr_
    }
  ),
  
  private = list(
    ptr_ = NULL
  )
)

