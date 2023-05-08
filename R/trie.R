#' Trie
#' 
#' @export
#' @rdname Trie
Trie <- R6::R6Class(
  "Trie",
  public = list(
    #' @param rootIdx a rootIdx
    #' @param maxChildren a maxChildren
    #' @return Trie
    initialize = function(maxChildren = NULL, rootIdx = NULL) {
      private$maxChildren_ <- maxChildren
      private$rootIdx_ <- rootIdx
      private$ptr_ <- cpp_Trie_constructor(maxChildren, rootIdx)
    },
    
    #' @return the root node pointer
    get_root = function() {
      cpp_Trie_getRoot(self$ptr)
    },
    
    #' @param indices a indices
    #' @param label a label
    #' @param score a score
    #' @return a TrieNodePtr
    insert = function(indices, label, score) {
      cpp_Trie_insert(self$ptr, indices, label, score)
    },
    
    #' @param indices a indices
    #' @return a TrieNodePtr
    search = function(indices) {
      cpp_Trie_search(self$ptr, indices)
    },
    
    
    #' @param smearMode a smearMode (see [SmearingModes] for options)
    #' @return invisible(NULL)
    smear = function(smearMode) {
      cpp_Trie_smear(self$ptr, smearMode)
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
    }
  ),
  
  private = list(
    ptr_ = NULL,
    maxChildren_ = NULL,
    rootIdx_ = NULL
  )
)

#' SmearingModes
#'
#' A enum (list) of semearing modes.
#'
#' @format ## `SmearingModes`
#' A list with 3 items:
#' \describe{
#'   \item{NONE}{Default = 0}
#'   \item{MAX}{Default = 1}
#'   \item{LOGADD}{Default = 2}
#' }
"SmearingModes"