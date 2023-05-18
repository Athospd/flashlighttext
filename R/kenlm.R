#' KenLM
#' 
#' @export
#' @rdname KenLM
KenLM <- R6::R6Class(
  "KenLM",
  inherit = LM,
  public = list(
    #' @param path a character string representing the path to the binary file containing the language model.
    #' @param usrTknDict a list of user-defined tokens.
    #' @return An instance of the KenLM class.
    initialize = function(path = NULL, usrTknDict = NULL) {
      private$path_ <- path
      private$usrTknDict_ <- usrTknDict
      private$ptr_ <- cpp_KenLMWrapper_constructor(path, usrTknDict$ptr)
    }
  ),
  
  active = list(
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
    path_ = NULL,
    usrTknDict_ = NULL
  )
)