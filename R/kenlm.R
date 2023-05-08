#' KenLM
#' 
#' @export
#' @rdname KenLM
KenLM <- R6::R6Class(
  "KenLM",
  public = list(
    #' @param path a path
    #' @param usrTknDict a usrTknDict
    #' @return KenLM
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
    },
    
    #' @param state a state
    #' @return list(LMState, numeric)
    finish = function(state) {
      cpp_KenLM_finish(self$ptr, state)
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
    #' path returns a string
    path = function() {
      private$path_
    },
    
    #' @field
    #' usrTknDict returns a string vector
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