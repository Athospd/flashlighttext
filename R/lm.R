#' LM
#' 
#' @export
#' @rdname LM
LM <- R6::R6Class(
  "LM",
  public = list(
    #' @return NULL
    initialize = function() {},
    
    #' @param startWithNothing a boolean
    #' @return LMState
    start = function(startWithNothing = FALSE) {
      stop("Tried to call pure virtual function 'LM::start'")
    },
    
    #' @param state a state
    #' @param usrTokenIdx a usrTokenIdx
    #' @return list(LMState, numeric)
    score = function(state, usrTokenIdx) {
      stop("Tried to call pure virtual function 'LM::score'")
    },
    
    #' @param state a state
    #' @return list(LMState, numeric)
    finish = function(state) {
      stop("Tried to call pure virtual function 'LM::finish'")
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