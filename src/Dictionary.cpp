#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include <Rcpp.h>
using namespace Rcpp;
#include <flashlight/lib/text/dictionary/Dictionary.h>
#include <flashlight/lib/text/dictionary/Utils.h>

using namespace fl::lib::text;

// constructors ------------------------------
// [[Rcpp::export]]
XPtr<Dictionary> cpp_Dictionary_constructor_empty() {
  Dictionary *obj = new Dictionary();
  XPtr<Dictionary> ptr(obj, true);
  return ptr;
}

// [[Rcpp::export]]
XPtr<Dictionary> cpp_Dictionary_constructor_string(const std::string& filename) {
  Dictionary *obj = new Dictionary(filename);
  XPtr<Dictionary> ptr(obj, true);
  return ptr;
}

// [[Rcpp::export]]
XPtr<Dictionary> cpp_Dictionary_constructor_vector_string(const std::vector<std::string>& tkns) {
  Dictionary *obj = new Dictionary(tkns);
  XPtr<Dictionary> ptr(obj, true);
  return ptr;
}

// methods ------------------------------
// [[Rcpp::export]]
size_t cpp_Dictionary_entry_size(XPtr<Dictionary> obj) {
  return obj->entrySize();
}

// [[Rcpp::export]]
size_t cpp_Dictionary_index_size(XPtr<Dictionary> obj) {
  return obj->indexSize();
}

// [[Rcpp::export]]
void cpp_Dictionary_add_entry_entry(XPtr<Dictionary> obj, const std::string& entry) {
  obj->addEntry(entry);
}

// [[Rcpp::export]]
void cpp_Dictionary_add_entry_entry_idx(XPtr<Dictionary> obj, const std::string& entry, int idx) {
  obj->addEntry(entry, idx);
}

// [[Rcpp::export]]
std::string cpp_Dictionary_get_entry(XPtr<Dictionary> obj, int idx) {
  return obj->getEntry(idx);
}

// [[Rcpp::export]]
Rcpp::NumericVector cpp_Dictionary_get_index(XPtr<Dictionary> obj, const std::vector<std::string>& entries) {
  Rcpp::NumericVector indeces(entries.size());
  for (std::size_t i = 0; i < entries.size(); i++) {
    indeces[i] = obj->getIndex(entries[i]);
  }
  return indeces;
}

// [[Rcpp::export]]
bool cpp_Dictionary_contains(XPtr<Dictionary> obj, const std::string& entry) {
  return obj->contains(entry);
}

// functions ------------------------------
// [[Rcpp::export]]
std::vector<int> cpp_Dictionary_pack_replabels(
    const std::vector<int>& tokens,
    XPtr<Dictionary> obj,
    int maxReps
) {
  Dictionary dict = *obj;
  return packReplabels(tokens, dict, maxReps);
}

// [[Rcpp::export]]
std::vector<int> cpp_Dictionary_unpack_replabels(
    const std::vector<int>& tokens,
    XPtr<Dictionary> obj,
    int maxReps
) {
  Dictionary dict = *obj;
  return unpackReplabels(tokens, dict, maxReps);
}

// [[Rcpp::export]]
void cpp_Dictionary_set_default_index(XPtr<Dictionary> obj, int idx) {
  obj->setDefaultIndex(idx);
}

// checks if all the indices are contiguous
// [[Rcpp::export]]
bool cpp_Dictionary_is_contiguous(XPtr<Dictionary> obj) {
  return obj->isContiguous();
}

// [[Rcpp::export]]
std::vector<int> cpp_Dictionary_map_entries_to_indices(
    XPtr<Dictionary> obj, 
    const std::vector<std::string>& entries
) {
  return obj->mapEntriesToIndices(entries);
}

// [[Rcpp::export]]
std::vector<std::string> cpp_Dictionary_map_indices_to_entries(
    XPtr<Dictionary> obj,
    const std::vector<int>& indices
) {
  return obj->mapIndicesToEntries(indices);
}

typedef std::string Key;
typedef std::vector<std::vector<std::string>> Value;

// [[Rcpp::export]]
List cpp_load_words2(const std::string& filename, int maxWords) {
  LexiconMap words = loadWords(filename, maxWords);
  
  auto key_selector = [](auto pair){return pair.first;};
  auto value_selector = [](auto pair){return pair.second;};
  
  // Vectors to hold keys and values
  std::vector<Key> keys(words.size());
  std::vector<Value> values(words.size());
  
  // This is the crucial bit: Transform words to list of keys (or values)
  std::transform(words.begin(), words.end(), keys.begin(), key_selector);
  std::transform(words.begin(), words.end(), values.begin(), value_selector);
  
  // further reshaping towards a named list is done on the R side.
  List output = Rcpp::List::create(
    Rcpp::Named("Keys") = keys,
    Rcpp::Named("Values") = values
  );
  return output;
}

// [[Rcpp::export]]
XPtr<Dictionary> cpp_create_word_dict(SEXP ptr, List lexicon) {
  std::vector<std::string> lexicon_keys = lexicon.names();
  LexiconMap lexicon_map;
  for (int i = 0; i < lexicon.size(); i++) {
    lexicon_map.insert({lexicon_keys[i], lexicon[i]});
  }
  Rcpp::XPtr<Dictionary> obj(ptr);
  *obj = createWordDict(lexicon_map);
  Rcpp::XPtr<Dictionary> ptr2(obj);
  return ptr2;
}
