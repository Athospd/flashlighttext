#' ZeroLM
#' 
#' @export
#' @rdname ZeroLM
ZeroLM <- R6::R6Class(
  "ZeroLM",
  public = list(
    #' @param path a path
    #' @param usrTknDict a usrTknDict
    #' @return ZeroLM
    initialize = function() {
      private$ptr_ <- cpp_ZeroLMWrapper_constructor()
    },
    
    #' @param startWithNothing a boolean
    #' @return LMState
    start = function(startWithNothing) {
      if(missing(startWithNothing)) startWithNothing <- FALSE
      cpp_ZeroLMWrapper_start(self$ptr, startWithNothing)
    },
    
    #' @param state a state
    #' @param usrTokenIdx a usrTokenIdx
    #' @return list(LMState, numeric)
    score = function(state, usrTokenIdx) {
      cpp_ZeroLMWrapper_score(self$ptr, state, usrTokenIdx)
    },
    
    #' @param state a state
    #' @return list(LMState, numeric)
    finish = function(state) {
      cpp_ZeroLMWrapper_finish(self$ptr, state)
    }
  ),
  
  active = list(
    #' @field 
    #' ptr has a single parameter new_ptr that accepts a new pointer to a ZeroLMWrapper.
    #' It returns invisible(NULL)
    ptr = function(new_ptr) {
      if(!missing(new_ptr)) private$ptr_ <- new_ptr
      private$ptr_
    }
  ),
  
  private = list(
    ptr_ = NULL
  )
)