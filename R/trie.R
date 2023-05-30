#' Trie
#' 
#' Trie is used to store the lexicon in language model. We use it to limit
#' the search space in decoder and quickly look up scores for a given token
#' (completed word) or make prediction for incompleted ones based on smearing.
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
    
    #' @description Insert a token into trie with label
    #' @param indices a indices
    #' @param label a label
    #' @param score a score
    #' @return a TrieNodePtr
    insert = function(indices, label, score) {
      trie_node <- TrieNode$new(0)
      if(length(indices) == 0) indices <- numeric(0)
      trie_node$ptr <- cpp_TrieWrapper_insert(self$ptr, indices, label, score)
      return(invisible(trie_node))
    },
    
    #' @description Get the labels for a given token
    #' @param indices a indices
    #' @return a TrieNodePtr
    search = function(indices) {
      trie_node <- TrieNode$new(0)
      trie_node$ptr <- cpp_TrieWrapper_search(self$ptr, indices)
      return(invisible(trie_node))
    },
    
    #' @description Smearing the trie using the valid labels inserted in the trie 
    #' so as to get score on each node (incompleted token).
    #' For example, if smear_mode is MAX, then for node "a" in path "c"->"a", we
    #' will select the maximum score from all its children like "c"->"a"->"t",
    #' "c"->"a"->"n", "c"->"a"->"r"->"e" and so on.
    #' This process will be carry out recursively on all the nodes.
    #' @param smearMode a smearMode (see [SmearingModes] for options)
    #' @return invisible(NULL)
    smear = function(smearMode) {
      cpp_TrieWrapper_smear(self$ptr, smearMode)
      return(invisible(self$ptr))
    }
  ),
  
  active = list(
    
    #' @field rootIdx the rootIdx.
    #' @field maxChildren The maximum number of children for each node. It is
    #' usually the size of letters or phonemes.
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



#' TrieNode
#' 
#' TrieNode is the trie node structure in Trie.
#' 
#' @export
#' @rdname TrieNode
TrieNode <- R6::R6Class(
  "TrieNode",
  public = list(
    #' @param idx an integer. Node index
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

#' Trie Builder
#'
#' Helper to build a trie with a Dictionary.
#'
#' @param lm a KenLM instance
#' @param lexicon a named list with the words and its tokens.
#' @param word_dict a Dictionary instance with the words. 
#' @param token_dict a DIctionary instance with the tokens.
#' @param separator_idx an integer. The index of the separator token.
#'
#' @returns a populated Trie instance.
#' @export
#'
#' @examples
#' library(flashlighttext)
#' lm <- ZeroLM$new()
#' lexicon <- list(
#'   "hello" = list(c("h", "e", "l", "l", "o", "|")),
#'   "world" = list(c("w", "o", "r", "l", "d", "|")),
#'   "<unk>" = list()
#' )
#' word_dict <- create_word_dict(lexicon)
#' token_dict <- Dictionary$new(c("h", "e", "l", "o", "|", "w", "r", "d", "<unk>")) 
#' token_dict$add_entry("<1>")
#' trie <- build_trie(
#'   lm = lm,
#'   token_dict = token_dict,
#'   lexicon = lexicon, 
#'   word_dict = word_dict,
#'   separator_idx = token_dict$get_index("|")
#' )
build_trie <- function(lm, token_dict, lexicon, word_dict, separator_idx) {
  trie <- Trie$new(token_dict$index_size(), separator_idx)
  start_state <- lm$start(FALSE)
  lexicon <- list2env(lexicon, hash = TRUE)
  for(word in names(lexicon)) {
    spellings <- lexicon[[word]]
    usr_idx <- word_dict$get_index(word)
    score <- lm$score(start_state, usr_idx)[[2]]
    for(spelling in spellings) {
      token_dict$map_entries_to_indices(spelling) %>%
        pack_replabels(token_dict, 1) %>%
        trie$insert(usr_idx, score)
    }
  }
  trie$smear(SmearingModes$MAX)
  return(trie)
}


