#' KenLM
#' 
#' @export
#' @rdname KenLM
KenLM <- R6::R6Class(
  "KenLM",
  inherit = LM,
  public = list(
    #' @param path a character string representing the path to the binary file 
    #' containing the language model.
    #' @param usrTknDict a Dictionary instance populated with user-defined tokens.
    #' @return An instance of the KenLM class.
    #' @examples
    #' library(flashlighttext)
    #' sys_file <- function(file) system.file(file, package = "flashlighttext")
    #' read_bin <- function(file, type, size) readBin(sys_file(file), size = size, type, n = 10000)
    #' 
    #' lexicon <- load_words(sys_file("words.lst")) 
    #' word_dict <- create_word_dict(lexicon) 
    #' lm <- KenLM$new(sys_file("lm.arpa"), word_dict) 
    #' lm_state <- lm$start(FALSE) 
    #' c(lm_state, lm_score) %<-% lm$score(lm_state, 0) 
    initialize = function(path = NULL, usrTknDict = NULL) {
      private$path_ <- path
      private$usrTknDict_ <- usrTknDict
      private$ptr_ <- cpp_KenLMWrapper_constructor(path, usrTknDict$ptr)
    }
  ),
  
  active = list(
    #' @field path returns a string
    path = function() {
      private$path_
    },
    
    #' @field usrTknDict returns a string vector
    usrTknDict = function() {
      private$usrTknDict_
    }
  ),
  
  private = list(
    path_ = NULL,
    usrTknDict_ = NULL
  )
)