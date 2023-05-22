#' LM
#' 
#' @export
LM <- R6::R6Class(
  "LM",
  public = list(
    #' @return NULL
    initialize = function() {
      # stop("LM is a base class and cannot be initialized. Instantiate ZeroLM or KenLM instead.")
    },
    
    #' @param startWithNothing a logical value indicating whether the state 
    #' should be initialized with a start-of-sequence marker.
    #' @return An LMState object representing the current state.
    start = function(startWithNothing) {
      cpp_LMWrapper_start(self$ptr, startWithNothing)
    },
    
    #' @param state An LMState object representing the current state.
    #' @param usrTokenIdx An integer representing the index of the current token 
    #' in the user-defined token list.
    #' @return A list containing the externalpointer to the updated LMState object
    #' and a numeric value representing the score.
    score = function(state, usrTokenIdx) {
      cpp_LMWrapper_score(self$ptr, state, usrTokenIdx)
    },
    
    #' @param state An LMState object representing the current state.
    #' @return A list containing the updated LMState object and a numeric value 
    #' representing the final score.
    finish = function(state) {
      cpp_LMWrapper_finish(self$ptr, state)
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

