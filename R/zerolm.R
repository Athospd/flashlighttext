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
    },
    
    #' @param startWithNothing a boolean
    #' @return LMState
    start = function(startWithNothing = FALSE) {
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
  )
)