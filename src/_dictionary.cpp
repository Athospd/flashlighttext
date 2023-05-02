/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <Rcpp.h>
// [[Rcpp::plugins(cpp11)]]

#include "flashlight/lib/text/decoder/lm/KenLM.h"
#include <string>

using namespace Rcpp;

#include "flashlight/lib/text/dictionary/Dictionary.h"
#include "flashlight/lib/text/dictionary/Utils.h"
using namespace fl::lib::text;

namespace {

void Dictionary_addEntry_0(
    Dictionary& dict,
    const std::string& entry,
    int idx) {
  dict.addEntry(entry, idx);
}

void Dictionary_addEntry_1(Dictionary& dict, const std::string& entry) {
  dict.addEntry(entry);
}

} // namespace

// constructors ------------------------------
// [[Rcpp::export]]
SEXP cpp_Dictionary_create_empty() {
  Dictionary *obj = new Dictionary();
  XPtr<Dictionary> ptr(obj, true);
  return ptr;
}

// [[Rcpp::export]]
SEXP cpp_Dictionary_create_string(const std::string& filename) {
  Dictionary *obj = new Dictionary(filename);
  XPtr<Dictionary> ptr(obj, true);
  return ptr;
}

// [[Rcpp::export]]
SEXP cpp_Dictionary_create_vector_string(const std::vector<std::string>& tkns) {
  Dictionary *obj = new Dictionary(tkns);
  XPtr<Dictionary> ptr(obj, true);
  return ptr;
}

// methods ------------------------------
// [[Rcpp::export]]
size_t cpp_Dictionary_entry_size(SEXP ptr) {
  Rcpp::XPtr<Dictionary> obj(ptr);
  return obj->entrySize();
}

// [[Rcpp::export]]
size_t cpp_Dictionary_index_size(SEXP ptr) {
  Rcpp::XPtr<Dictionary> obj(ptr);
  return obj->indexSize();
}

// [[Rcpp::export]]
void cpp_Dictionary_add_entry_entry(SEXP ptr, const std::string& entry) {
  Rcpp::XPtr<Dictionary> obj(ptr);
  return obj->addEntry(entry);
}

// [[Rcpp::export]]
void cpp_Dictionary_add_entry_entry_idx(SEXP ptr, const std::string& entry, int idx) {
  Rcpp::XPtr<Dictionary> obj(ptr);
  return obj->addEntry(entry, idx);
}

// [[Rcpp::export]]
std::string cpp_Dictionary_get_entry(SEXP ptr, int idx) {
  Rcpp::XPtr<Dictionary> obj(ptr);
  return obj->getEntry(idx);
}

// [[Rcpp::export]]
int cpp_Dictionary_get_index(SEXP ptr, const std::string& entry) {
  Rcpp::XPtr<Dictionary> obj(ptr);
  return obj->getIndex(entry);
}

// [[Rcpp::export]]
bool cpp_Dictionary_contains(SEXP ptr, const std::string& entry) {
  Rcpp::XPtr<Dictionary> obj(ptr);
  return obj->contains(entry);
}

// functions ------------------------------
// [[Rcpp::export]]
std::vector<int> cpp_Dictionary_pack_replabels(
  const std::vector<int>& tokens,
  SEXP ptr,
  int maxReps
) {
  Rcpp::XPtr<Dictionary> obj(ptr);
  Dictionary dict = *obj;
  return packReplabels(tokens, dict, maxReps);
}

// [[Rcpp::export]]
std::vector<int> cpp_Dictionary_unpack_replabels(
    const std::vector<int>& tokens,
    SEXP ptr,
    int maxReps
) {
  Rcpp::XPtr<Dictionary> obj(ptr);
  Dictionary dict = *obj;
  return unpackReplabels(tokens, dict, maxReps);
}

// [[Rcpp::export]]
void cpp_Dictionary_set_default_index(SEXP ptr, int idx) {
  Rcpp::XPtr<Dictionary> obj(ptr);
  obj->setDefaultIndex(idx);
}

// checks if all the indices are contiguous
// [[Rcpp::export]]
bool cpp_Dictionary_is_contiguous(SEXP ptr) {
  Rcpp::XPtr<Dictionary> obj(ptr);
  return obj->isContiguous();
}

// [[Rcpp::export]]
std::vector<int> cpp_Dictionary_map_entries_to_indices(
  SEXP ptr, 
  const std::vector<std::string>& entries
) {
  Rcpp::XPtr<Dictionary> obj(ptr);
  return obj->mapEntriesToIndices(entries);
}

// [[Rcpp::export]]
std::vector<std::string> cpp_Dictionary_map_indices_to_entries(
  SEXP ptr,
  const std::vector<int>& indices
) {
  Rcpp::XPtr<Dictionary> obj(ptr);
  return obj->mapIndicesToEntries(indices);
}

// // [[Rcpp::export]]
// LexiconMap cpp_Dictionary_load_words(const std::string& filename, int maxWords) {
//   return loadWords(filename, maxWords);
// }

template <typename T>
List unordered_map_to_list(std::unordered_map<T, T> umap) {
  List output;
  for (auto& item: umap) {
    output[item.first] = item.second;
  }
  return output;
}

// [[Rcpp::export]]
List cpp_load_words(const std::string& filename, int maxWords) {
  LexiconMap words = loadWords(filename, maxWords);
  List output;
  for (auto& word: words) {
    output[word.first] = word.second;
  }
  return output;
}

// [[Rcpp::export]]
SEXP cpp_create_word_dict(List lexicon) {
  std::vector<std::string> lexicon_keys = lexicon.names();
  LexiconMap lexicon_map;
  for (int i = 0; i < lexicon.size(); i++) {
    lexicon_map.insert({lexicon_keys[i], lexicon[i]});
    std::cout << lexicon_keys[i] << ": " << i <<  std::endl;
  }
  Dictionary dict = createWordDict(lexicon_map);
  
  for (int i = 0; i < lexicon.size(); i++) {
    std::string entry = dict.getEntry(i);
    int index = dict.getIndex(entry);
    std::cout << entry << ":" << index << " | ";
  }
  std::cout << dict.g << ":" << index << " | ";  
  Dictionary* out = new Dictionary();
  out = &dict;
  XPtr<Dictionary> ptr(out, true);
  return ptr;
}

// RCPP_EXPOSED_AS(Dictionary);

// RCPP_MODULE(flashlight_lib_text_dictionary) {
  // Rcpp::class_<Dictionary>("Dictionary")
  // .constructor<std::istream>()
  
  // function("create_word_dict", &createWordDict, List::create(_["lexicon"]));
  // function("load_words", &loadWords, List::create(_["filename"], _["max_words"] = -1));
// }

// PYBIND11_MODULE(flashlight_lib_text_dictionary, m) {
//   py::class_<Dictionary>(m, "Dictionary")
//       .def(py::init<>())
//       .def(py::init<const std::string&>(), "filename"_a)
//       .def(py::init<const std::vector<std::string>&>(), "tkns"_a)
//       .def("entry_size", &Dictionary::entrySize)
//       .def("index_size", &Dictionary::indexSize)
//       .def("add_entry", &Dictionary_addEntry_0, "entry"_a, "idx"_a)
//       .def("add_entry", &Dictionary_addEntry_1, "entry"_a)
//       .def("get_entry", &Dictionary::getEntry, "idx"_a)
//       .def("set_default_index", &Dictionary::setDefaultIndex, "idx"_a)
//       .def("get_index", &Dictionary::getIndex, "entry"_a)
//       .def("contains", &Dictionary::contains, "entry"_a)
//       .def("is_contiguous", &Dictionary::isContiguous)
//       .def(
//           "map_entries_to_indices",
//           &Dictionary::mapEntriesToIndices,
//           "entries"_a)
//       .def(
//           "map_indices_to_entries",
//           &Dictionary::mapIndicesToEntries,
//           "indices"_a);
//   m.def("create_word_dict", &createWordDict, "lexicon"_a);
//   m.def("load_words", &loadWords, "filename"_a, "max_words"_a = -1);
//   m.def("pack_replabels", &packReplabels, "tokens"_a, "dict"_a, "max_reps"_a);
//   m.def(
//       "unpack_replabels", &unpackReplabels, "tokens"_a, "dict"_a, "max_reps"_a);
// }

/*** R
# a <- new(flashlighttext::Dictionary, "a.txt")
# a$index_size()
*/

