#' Dictionary
#' @export
#' @rdname Dictionary
#'
#' @examples
#'
#' library(flashlighttext)
#'
#' dict <- Dictionary$new()
Dictionary <- R6::R6Class(
  "Dictionary",
  public = list(
    
    #' @param filename path to a file
    #' @param tkns tokens
    #' @return Dictionary
    initialize = function(filename = NULL, tkns = NULL) {
      if(!is.null(filename)) {
        private$filename_ <- filename
        private$ptr_ <- cpp_Dictionary_constructor_string(filename)
      } else if (!is.null(tkns)) {
        private$tokens_ <- tkns
        private$ptr_ <- cpp_Dictionary_constructor_vector_string(tokens)
      } else {
        private$ptr_ <- cpp_Dictionary_constructor_empty()
      }
    },
    
    #' @return invisible(NULL)
    entry_size = function() {
      cpp_Dictionary_entry_size(self$ptr)
    },
    
    #' @return invisible(NULL)
    index_size = function() {
      cpp_Dictionary_index_size(self$ptr)
    },
    
    #' @param entry an entry
    #' @param idx an idx
    #' @return invisible(NULL)
    add_entry = function(entry, idx = NULL) {
      if(!is.null(idx)) {
        cpp_Dictionary_add_entry_entry_idx(self$ptr, entry, idx)
      } else {
        cpp_Dictionary_add_entry_entry(self$ptr, entry)  
      }
    },
    
    #' @param entry an entry
    #' @return the index
    get_index = function(entry) {
      cpp_Dictionary_get_index(self$ptr, entry)
    },
    
    #' @param idx an index
    #' @return the entry
    get_entry = function(idx) {
      cpp_Dictionary_get_entry(self$ptr, idx)
    },
    
    #' @param entry an entry
    #' @return a boolean
    contains = function(entry) {
      cpp_Dictionary_contains(self$ptr, entry)
    },
    
    #' @param indices a vector of indices
    #' @return a vector
    map_indices_to_entries = function(indices) {
      cpp_Dictionary_map_indices_to_entries(self$ptr, indices)
    },
    
    #' @param entries a vector of entries
    #' @return a vector
    map_entries_to_indices = function(entries) {
      cpp_Dictionary_map_entries_to_indices(self$ptr, entries)
    },
    
    #' @return a boolean
    is_contiguous = function() {
      cpp_Dictionary_is_contiguous(self$ptr)
    },
    
    #' @param idx one index
    #' @return invisible(NULL)
    set_default_index = function(idx) {
      cpp_Dictionary_set_default_index(self$ptr, idx)
    }
  ),
  
  active = list(
    
    #' @field 
    #' ptr has a single parameter new_ptr that accepts a new pointer to a Dictionary.
    #' It returns invisible(NULL)
    ptr = function(new_ptr) {
      if(!missing(new_ptr)) {
        private$ptr_ <- new_ptr
      }
        
      if(is_null_externalptr(private$ptr_)) 
        private$ptr_ <- cpp_Dictionary_constructor()
      
      private$ptr_
    },
    
    #' @field
    #' filename returns a string
    filename = function() {
      private$filename_
    },
    
    #' @field
    #' tokens returns a string vector
    tokens = function() {
      private$tokens_
    }
  ),
  
  private = list(
    ptr_ = NULL,
    filename_ = NULL,
    tokens_ = NULL
  )
)

#' pack_replabels
#'
#' @param tokens int vector
#' @param dict Dictionary instance
#' @param max_reps atomic int
#'
#' @return int vector
#' @export
pack_replabels <- function(tokens, dict, max_reps) {
  cpp_Dictionary_pack_replabels(tokens, dict$ptr, max_reps)
}

#' unpack_replabels
#'
#' @param tokens int vector
#' @param dict Dictionary instance
#' @param max_reps atomic int
#'
#' @return int vector
#' @export
unpack_replabels <- function(tokens, dict, max_reps) {
  cpp_Dictionary_unpack_replabels(tokens, dict$ptr, max_reps)
}

#' load_words
#'
#' @param filename a string 
#' @param maxWords an int
#'
#' @return LexiconMap
#' @export
load_words <- function(filename, maxWords = -1) {
  cpp_load_words(filename, maxWords)
}

#' create_word_dict
#'
#' @param lexicon a named list of vectors.
#'
#' @return Dictionary
#' @export
create_word_dict <- function(lexicon) {
  dict <- Dictionary$new()
  dict$ptr <- cpp_create_word_dict(dict$ptr, lexicon)
  return(dict)
}

