#' KenLM
#' 
#' @export
#' @rdname KenLM
KenLM <- R6::R6Class(
  "KenLM",
  public = list(
    #' @param path a character string representing the path to the binary file containing the language model.
    #' @param usrTknDict a list of user-defined tokens.
    #' @return An instance of the KenLM class.
    initialize = function(path = NULL, usrTknDict = NULL) {
      private$path_ <- path
      private$usrTknDict_ <- usrTknDict
      private$ptr_ <- cpp_KenLMWrapper_constructor(path, usrTknDict$ptr)
    },
    
    #' @param startWithNothing a logical value indicating whether the state should be initialized with a start-of-sequence marker.
    #' @return An LMState object representing the current state.
    start = function(startWithNothing) {
      cpp_KenLMWrapper_start(self$ptr, startWithNothing)
    },
    
    #' @param state An LMState object representing the current state.
    #' @param usrTokenIdx An integer representing the index of the current token in the user-defined token list.
    #' @return A list containing the updated LMState object and a numeric value representing the score.
    score = function(state, usrTokenIdx) {
      cpp_KenLMWrapper_score(self$ptr, state, usrTokenIdx)
    },
    
    #' @param state An LMState object representing the current state.
    #' @return A list containing the updated LMState object and a numeric value representing the final score.
    finish = function(state) {
      cpp_KenLMWrapper_finish(self$ptr, state)
    }
  ),
  
  active = list(
    #' @field 
    #' ptr has a single parameter new_ptr that accepts a new pointer to a KenLMWrapper.
    #' It returns invisible(NULL)
    ptr = function(new_ptr) {
      if(!missing(new_ptr))  private$ptr_ <- new_ptr
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