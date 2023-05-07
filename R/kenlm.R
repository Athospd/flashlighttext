#' KenLM
#' 
#' @export
#' @rdname KenLM
KenLM <- R6::R6Class(
  "KenLM",
  public = list(
    initialize = function(path = NULL, usrTknDict = NULL) {
      private$path_ <- path
      private$usrTknDict_ <- usrTknDict
      private$ptr_ <- cpp_KenLM_constructor(path, usrTknDict$ptr)
    },
    
    #' @param startWithNothing a boolean
    #' @return LMState
    start = function(startWithNothing) {
      cpp_KenLM_start(self$ptr, startWithNothing)
    },
    
    #' @param state a state
    #' @param usrTokenIdx a usrTokenIdx
    #' @return list(LMState, numeric)
    score = function(state, usrTokenIdx) {
      cpp_KenLM_score(self$ptr, state, usrTokenIdx)
    }
  ),
  
  active = list(
    
    #' @field 
    #' ptr has a single parameter new_ptr that accepts a new pointer to a KenLM.
    #' It returns invisible(NULL)
    ptr = function(new_ptr) {
      if(!missing(new_ptr)) {
        private$ptr_ <- new_ptr
      }
      
      private$ptr_
    },
    
    #' @field
    #' filename returns a string
    path = function() {
      private$path_
    },
    
    #' @field
    #' tokens returns a string vector
    usrTknDict = function() {
      private$usrTknDict_
    }
  ),
  
  private = list(
    ptr_ = NULL,
    path_ = NULL,
    usrTknDict_ = NULL
  )
)