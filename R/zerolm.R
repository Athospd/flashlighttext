#' ZeroLM
#' 
#' @export
#' @rdname ZeroLM
ZeroLM <- R6::R6Class(
  "ZeroLM",
  inherit = LM,
  public = list(
    #' @param path a path
    #' @param usrTknDict a usrTknDict
    #' @return ZeroLM
    initialize = function() {
      private$ptr_ <- cpp_ZeroLMWrapper_constructor()
    }
  )
)