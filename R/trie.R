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
      private$ptr_ <- cpp_TrieWrapper_constructor(maxChildren, rootIdx)
    },
    
    #' @return the root node pointer
    get_root = function() {
      invisible(cpp_TrieWrapper_getRoot(self$ptr))
    },
    
    #' @param indices a indices
    #' @param label a label
    #' @param score a score
    #' @return a TrieNodePtr
    insert = function(indices, label, score) {
      trie_node <- TrieNode$new(0)
      trie_node$ptr <- cpp_TrieWrapper_insert(self$ptr, indices, label, score)
      return(invisible(trie_node))
    },
    
    #' @param indices a indices
    #' @return a TrieNodePtr
    search = function(indices) {
      trie_node <- TrieNode$new(0)
      trie_node$ptr <- cpp_TrieWrapper_search(self$ptr, indices)
      return(invisible(trie_node))
    },
    
    
    #' @param smearMode a smearMode (see [SmearingModes] for options)
    #' @return invisible(NULL)
    smear = function(smearMode) {
      cpp_TrieWrapper_smear(self$ptr, smearMode)
      invisible(self$ptr)
    }
  ),
  
  active = list(
    
    #' @field rootIdx the rootIdx.
    #' @field maxChildren The maximum number of childern for each node. It is
    #' usually the size of letters or phonmes.
    #' @field ptr set and get the pointer to a Trie instance.
    ptr = function(new_ptr) {
      if(!missing(new_ptr)) private$ptr_ <- new_ptr
      private$ptr_
    },
    maxChildren = function() private$maxChildren_,
    rootIdx = function() private$rootIdx_
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
#'   \item{NONE}{string "NONE"}
#'   \item{MAX}{string "MAX"}
#'   \item{LOGADD}{string "LOGADD"}
#' }
"SmearingModes"


#' TrieNode
#' 
#' @export
#' @rdname TrieNode
TrieNode <- R6::R6Class(
  "TrieNode",
  public = list(
    #' @param idx a idx
    #' @return TrieNode
    initialize = function(idx = NULL) {
      private$idx_ <- idx
      private$ptr_ <- cpp_TrieNode_constructor(idx)
    },
    
    #' @return the node max score
    max_score = function() {
      cpp_TrieNode_maxScore(self$ptr)
    }
  ),
  
  active = list(
    
    #' @field 
    #' ptr has a single parameter new_ptr that accepts a new pointer to a TrieNode.
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
    idx_ = NULL
  )
)
