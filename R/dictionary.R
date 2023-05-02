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
    initialize = function(filename = NULL, tkns = NULL) {
      if(!is.null(filename)) {
        private$filename_ <- filename
        private$ptr_ <- cpp_Dictionary_create_string(filename)
      } else if (!is.null(tkns)) {
        private$tokens_ <- tkns
        private$ptr_ <- cpp_Dictionary_create_vector_string(tokens)
      } else {
        private$ptr_ <- cpp_Dictionary_create_empty()
      }
    },
    entry_size = function() {
      cpp_Dictionary_entry_size(self$ptr)
    },
    
    index_size = function() {
      cpp_Dictionary_index_size(self$ptr)
    },
    
    add_entry = function(entry, idx = NULL) {
      if(!is.null(idx)) {
        cpp_Dictionary_add_entry_entry_idx(self$ptr, entry, idx)
      } else {
        cpp_Dictionary_add_entry_entry(self$ptr, entry)  
      }
    },
    
    get_index = function(entry) {
      cpp_Dictionary_get_index(self$ptr, entry)
    },
    
    get_entry = function(idx) {
      cpp_Dictionary_get_entry(self$ptr, idx)
    },
    
    contains = function(entry) {
      cpp_Dictionary_contains(self$ptr, entry)
    },
    
    map_indices_to_entries = function(indices) {
      cpp_Dictionary_map_indices_to_entries(self$ptr, indices)
    },
    
    map_entries_to_indices = function(entries) {
      cpp_Dictionary_map_entries_to_indices(self$ptr, entries)
    },
    
    is_contiguous = function() {
      cpp_Dictionary_is_contiguous(self$ptr)
    },
    
    set_default_index = function(idx) {
      cpp_Dictionary_set_default_index(self$ptr, idx)
    }
  ),
  
  active = list(
    ptr = function(new_ptr) {
      if(!missing(new_ptr)) {
        private$ptr_ <- new_ptr
      }
        
      if(is_null_externalptr(private$ptr_)) 
        private$ptr_ <- cpp_Dictionary_create()
      
      private$ptr_
    },
    
    filename = function() {
      private$filename_
    },
    
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
load_words <- function(filename, maxWords) {
  cpp_load_words(filename, maxWords)
}

#' create_word_dict
#'
#' @param lexicon a named list of vectors.
#'
#' @return
#' @export
#'
#' @examples
create_word_dict <- function(lexicon) {
  dict <- Dictionary$new()
  dict$ptr <- cpp_create_word_dict(lexicon)
  return(dict)
}

