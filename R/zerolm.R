#' ZeroLM
#' 
#' ZeroLM is a dummy language model class, which mimics the behaviour of a
#' uni-gram language model but always returns 0 as score.
#' 
#' @export
#' @rdname ZeroLM
ZeroLM <- R6::R6Class(
  "ZeroLM",
  inherit = LM,
  public = list(
    #' @return ZeroLM
    initialize = function() {
      private$ptr_ <- cpp_ZeroLMWrapper_constructor()
    }
  )
)