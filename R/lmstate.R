#' LMState
#' 
#' @export
#' @rdname LMState
LMState <- R6::R6Class(
  "LMState",
  public = list(
    
    #' @return An instance of the LMState class.
    initialize = function() {
      private$ptr_ <- cpp_LMStateWrapper_constructor()
    },
    
    #' @param usr_index a usr_index
    #' @return externalpointer to a LMStateWrapper
    child = function(usr_index) {
      if(!is.numeric(usr_index)) 
        stop(f("usr_index should be an integer. Got {toString(class(usr_index))}."))
      # TO DO
      # lmstate_ptr <- cpp_LMStateWrapper_child(self$ptr, usr_index)
      # lmstate_ptr_to_r(lmstate_ptr)
      
      cpp_LMStateWrapper_child(self$ptr, usr_index)
    },
    
    #' @param state an externalpointer to a LMState to compare with.
    #' @return int
    compare = function(state) {
      cpp_LMStateWrapper_compare(self$ptr, state)
    }
  ),
  
  active = list(
    #' @field 
    #' ptr get or set a pointer to a LMStateWrapper.
    ptr = function(new_ptr) {
      if(!missing(new_ptr)) private$ptr_ <- new_ptr
      private$ptr_
    },
    
    #' @field children a list of pairs (index, LMStatePtr)
    children = function() {
      c(indices, lm_states) %<-% cpp_LMStateWrapper_children(self$ptr)
      # TO DO
      # lm_states <- purrr::map(lm_states, lmstate_ptr_to_r)
      attr(lm_states, "names") <- indices
      return(lm_states)
    }
  ),
  
  private = list(
    ptr_ = NULL
  )
)