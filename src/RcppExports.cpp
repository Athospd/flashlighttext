// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

#ifdef RCPP_USE_GLOBAL_ROSTREAM
Rcpp::Rostream<true>&  Rcpp::Rcout = Rcpp::Rcpp_cout_get();
Rcpp::Rostream<false>& Rcpp::Rcerr = Rcpp::Rcpp_cerr_get();
#endif

// cpp_Dictionary_create_empty
SEXP cpp_Dictionary_create_empty();
RcppExport SEXP _flashlighttext_cpp_Dictionary_create_empty() {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    rcpp_result_gen = Rcpp::wrap(cpp_Dictionary_create_empty());
    return rcpp_result_gen;
END_RCPP
}
// cpp_Dictionary_create_string
SEXP cpp_Dictionary_create_string(const std::string& filename);
RcppExport SEXP _flashlighttext_cpp_Dictionary_create_string(SEXP filenameSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::string& >::type filename(filenameSEXP);
    rcpp_result_gen = Rcpp::wrap(cpp_Dictionary_create_string(filename));
    return rcpp_result_gen;
END_RCPP
}
// cpp_Dictionary_create_vector_string
SEXP cpp_Dictionary_create_vector_string(const std::vector<std::string>& tkns);
RcppExport SEXP _flashlighttext_cpp_Dictionary_create_vector_string(SEXP tknsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::vector<std::string>& >::type tkns(tknsSEXP);
    rcpp_result_gen = Rcpp::wrap(cpp_Dictionary_create_vector_string(tkns));
    return rcpp_result_gen;
END_RCPP
}
// cpp_Dictionary_entry_size
size_t cpp_Dictionary_entry_size(SEXP ptr);
RcppExport SEXP _flashlighttext_cpp_Dictionary_entry_size(SEXP ptrSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type ptr(ptrSEXP);
    rcpp_result_gen = Rcpp::wrap(cpp_Dictionary_entry_size(ptr));
    return rcpp_result_gen;
END_RCPP
}
// cpp_Dictionary_index_size
size_t cpp_Dictionary_index_size(SEXP ptr);
RcppExport SEXP _flashlighttext_cpp_Dictionary_index_size(SEXP ptrSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type ptr(ptrSEXP);
    rcpp_result_gen = Rcpp::wrap(cpp_Dictionary_index_size(ptr));
    return rcpp_result_gen;
END_RCPP
}
// cpp_Dictionary_add_entry_entry
void cpp_Dictionary_add_entry_entry(SEXP ptr, const std::string& entry);
RcppExport SEXP _flashlighttext_cpp_Dictionary_add_entry_entry(SEXP ptrSEXP, SEXP entrySEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type ptr(ptrSEXP);
    Rcpp::traits::input_parameter< const std::string& >::type entry(entrySEXP);
    cpp_Dictionary_add_entry_entry(ptr, entry);
    return R_NilValue;
END_RCPP
}
// cpp_Dictionary_add_entry_entry_idx
void cpp_Dictionary_add_entry_entry_idx(SEXP ptr, const std::string& entry, int idx);
RcppExport SEXP _flashlighttext_cpp_Dictionary_add_entry_entry_idx(SEXP ptrSEXP, SEXP entrySEXP, SEXP idxSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type ptr(ptrSEXP);
    Rcpp::traits::input_parameter< const std::string& >::type entry(entrySEXP);
    Rcpp::traits::input_parameter< int >::type idx(idxSEXP);
    cpp_Dictionary_add_entry_entry_idx(ptr, entry, idx);
    return R_NilValue;
END_RCPP
}
// cpp_Dictionary_get_entry
std::string cpp_Dictionary_get_entry(SEXP ptr, int idx);
RcppExport SEXP _flashlighttext_cpp_Dictionary_get_entry(SEXP ptrSEXP, SEXP idxSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type ptr(ptrSEXP);
    Rcpp::traits::input_parameter< int >::type idx(idxSEXP);
    rcpp_result_gen = Rcpp::wrap(cpp_Dictionary_get_entry(ptr, idx));
    return rcpp_result_gen;
END_RCPP
}
// cpp_Dictionary_get_index
int cpp_Dictionary_get_index(SEXP ptr, const std::string& entry);
RcppExport SEXP _flashlighttext_cpp_Dictionary_get_index(SEXP ptrSEXP, SEXP entrySEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type ptr(ptrSEXP);
    Rcpp::traits::input_parameter< const std::string& >::type entry(entrySEXP);
    rcpp_result_gen = Rcpp::wrap(cpp_Dictionary_get_index(ptr, entry));
    return rcpp_result_gen;
END_RCPP
}
// cpp_Dictionary_contains
bool cpp_Dictionary_contains(SEXP ptr, const std::string& entry);
RcppExport SEXP _flashlighttext_cpp_Dictionary_contains(SEXP ptrSEXP, SEXP entrySEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type ptr(ptrSEXP);
    Rcpp::traits::input_parameter< const std::string& >::type entry(entrySEXP);
    rcpp_result_gen = Rcpp::wrap(cpp_Dictionary_contains(ptr, entry));
    return rcpp_result_gen;
END_RCPP
}
// cpp_Dictionary_pack_replabels
std::vector<int> cpp_Dictionary_pack_replabels(const std::vector<int>& tokens, SEXP ptr, int maxReps);
RcppExport SEXP _flashlighttext_cpp_Dictionary_pack_replabels(SEXP tokensSEXP, SEXP ptrSEXP, SEXP maxRepsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::vector<int>& >::type tokens(tokensSEXP);
    Rcpp::traits::input_parameter< SEXP >::type ptr(ptrSEXP);
    Rcpp::traits::input_parameter< int >::type maxReps(maxRepsSEXP);
    rcpp_result_gen = Rcpp::wrap(cpp_Dictionary_pack_replabels(tokens, ptr, maxReps));
    return rcpp_result_gen;
END_RCPP
}
// cpp_Dictionary_unpack_replabels
std::vector<int> cpp_Dictionary_unpack_replabels(const std::vector<int>& tokens, SEXP ptr, int maxReps);
RcppExport SEXP _flashlighttext_cpp_Dictionary_unpack_replabels(SEXP tokensSEXP, SEXP ptrSEXP, SEXP maxRepsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::vector<int>& >::type tokens(tokensSEXP);
    Rcpp::traits::input_parameter< SEXP >::type ptr(ptrSEXP);
    Rcpp::traits::input_parameter< int >::type maxReps(maxRepsSEXP);
    rcpp_result_gen = Rcpp::wrap(cpp_Dictionary_unpack_replabels(tokens, ptr, maxReps));
    return rcpp_result_gen;
END_RCPP
}
// cpp_Dictionary_set_default_index
void cpp_Dictionary_set_default_index(SEXP ptr, int idx);
RcppExport SEXP _flashlighttext_cpp_Dictionary_set_default_index(SEXP ptrSEXP, SEXP idxSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type ptr(ptrSEXP);
    Rcpp::traits::input_parameter< int >::type idx(idxSEXP);
    cpp_Dictionary_set_default_index(ptr, idx);
    return R_NilValue;
END_RCPP
}
// cpp_Dictionary_is_contiguous
bool cpp_Dictionary_is_contiguous(SEXP ptr);
RcppExport SEXP _flashlighttext_cpp_Dictionary_is_contiguous(SEXP ptrSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type ptr(ptrSEXP);
    rcpp_result_gen = Rcpp::wrap(cpp_Dictionary_is_contiguous(ptr));
    return rcpp_result_gen;
END_RCPP
}
// cpp_Dictionary_map_entries_to_indices
std::vector<int> cpp_Dictionary_map_entries_to_indices(SEXP ptr, const std::vector<std::string>& entries);
RcppExport SEXP _flashlighttext_cpp_Dictionary_map_entries_to_indices(SEXP ptrSEXP, SEXP entriesSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type ptr(ptrSEXP);
    Rcpp::traits::input_parameter< const std::vector<std::string>& >::type entries(entriesSEXP);
    rcpp_result_gen = Rcpp::wrap(cpp_Dictionary_map_entries_to_indices(ptr, entries));
    return rcpp_result_gen;
END_RCPP
}
// cpp_Dictionary_map_indices_to_entries
std::vector<std::string> cpp_Dictionary_map_indices_to_entries(SEXP ptr, const std::vector<int>& indices);
RcppExport SEXP _flashlighttext_cpp_Dictionary_map_indices_to_entries(SEXP ptrSEXP, SEXP indicesSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type ptr(ptrSEXP);
    Rcpp::traits::input_parameter< const std::vector<int>& >::type indices(indicesSEXP);
    rcpp_result_gen = Rcpp::wrap(cpp_Dictionary_map_indices_to_entries(ptr, indices));
    return rcpp_result_gen;
END_RCPP
}
// cpp_load_words
List cpp_load_words(const std::string& filename, int maxWords);
RcppExport SEXP _flashlighttext_cpp_load_words(SEXP filenameSEXP, SEXP maxWordsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::string& >::type filename(filenameSEXP);
    Rcpp::traits::input_parameter< int >::type maxWords(maxWordsSEXP);
    rcpp_result_gen = Rcpp::wrap(cpp_load_words(filename, maxWords));
    return rcpp_result_gen;
END_RCPP
}
// cpp_create_word_dict
SEXP cpp_create_word_dict(List lexicon);
RcppExport SEXP _flashlighttext_cpp_create_word_dict(SEXP lexiconSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type lexicon(lexiconSEXP);
    rcpp_result_gen = Rcpp::wrap(cpp_create_word_dict(lexicon));
    return rcpp_result_gen;
END_RCPP
}

RcppExport SEXP _rcpp_module_boot_flashlight_lib_text_decoder_kenlm();

static const R_CallMethodDef CallEntries[] = {
    {"_flashlighttext_cpp_Dictionary_create_empty", (DL_FUNC) &_flashlighttext_cpp_Dictionary_create_empty, 0},
    {"_flashlighttext_cpp_Dictionary_create_string", (DL_FUNC) &_flashlighttext_cpp_Dictionary_create_string, 1},
    {"_flashlighttext_cpp_Dictionary_create_vector_string", (DL_FUNC) &_flashlighttext_cpp_Dictionary_create_vector_string, 1},
    {"_flashlighttext_cpp_Dictionary_entry_size", (DL_FUNC) &_flashlighttext_cpp_Dictionary_entry_size, 1},
    {"_flashlighttext_cpp_Dictionary_index_size", (DL_FUNC) &_flashlighttext_cpp_Dictionary_index_size, 1},
    {"_flashlighttext_cpp_Dictionary_add_entry_entry", (DL_FUNC) &_flashlighttext_cpp_Dictionary_add_entry_entry, 2},
    {"_flashlighttext_cpp_Dictionary_add_entry_entry_idx", (DL_FUNC) &_flashlighttext_cpp_Dictionary_add_entry_entry_idx, 3},
    {"_flashlighttext_cpp_Dictionary_get_entry", (DL_FUNC) &_flashlighttext_cpp_Dictionary_get_entry, 2},
    {"_flashlighttext_cpp_Dictionary_get_index", (DL_FUNC) &_flashlighttext_cpp_Dictionary_get_index, 2},
    {"_flashlighttext_cpp_Dictionary_contains", (DL_FUNC) &_flashlighttext_cpp_Dictionary_contains, 2},
    {"_flashlighttext_cpp_Dictionary_pack_replabels", (DL_FUNC) &_flashlighttext_cpp_Dictionary_pack_replabels, 3},
    {"_flashlighttext_cpp_Dictionary_unpack_replabels", (DL_FUNC) &_flashlighttext_cpp_Dictionary_unpack_replabels, 3},
    {"_flashlighttext_cpp_Dictionary_set_default_index", (DL_FUNC) &_flashlighttext_cpp_Dictionary_set_default_index, 2},
    {"_flashlighttext_cpp_Dictionary_is_contiguous", (DL_FUNC) &_flashlighttext_cpp_Dictionary_is_contiguous, 1},
    {"_flashlighttext_cpp_Dictionary_map_entries_to_indices", (DL_FUNC) &_flashlighttext_cpp_Dictionary_map_entries_to_indices, 2},
    {"_flashlighttext_cpp_Dictionary_map_indices_to_entries", (DL_FUNC) &_flashlighttext_cpp_Dictionary_map_indices_to_entries, 2},
    {"_flashlighttext_cpp_load_words", (DL_FUNC) &_flashlighttext_cpp_load_words, 2},
    {"_flashlighttext_cpp_create_word_dict", (DL_FUNC) &_flashlighttext_cpp_create_word_dict, 1},
    {"_rcpp_module_boot_flashlight_lib_text_decoder_kenlm", (DL_FUNC) &_rcpp_module_boot_flashlight_lib_text_decoder_kenlm, 0},
    {NULL, NULL, 0}
};

RcppExport void R_init_flashlighttext(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
