#include <stdexcept>
#include <Rcpp.h>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdint>
using namespace Rcpp;
#include <flashlight/lib/text/decoder/Decoder.h>
#include <flashlight/lib/text/dictionary/Utils.h>
#include <flashlight/lib/text/dictionary/Dictionary.h>
#include <flashlight/lib/text/decoder/lm/KenLM.h>
#include <flashlight/lib/text/decoder/Trie.h>
#include "wrappers.h"
using namespace fl::lib::text;


// methods ------------------------------
// [[Rcpp::export]]
void cpp_Decoder_decodeBegin(XPtr<Decoder> obj) {
  obj->decodeBegin();
}

// [[Rcpp::export]]
void cpp_Decoder_decodeStep(XPtr<Decoder> obj, std::vector<float>& emissions, int T, int N) {
  float *emissions_ = emissions.data();
  obj->decodeStep(emissions_, T, N);
}

// [[Rcpp::export]]
void cpp_Decoder_decodeEnd(XPtr<Decoder> obj) {
  obj->decodeEnd();
}

// [[Rcpp::export]]
List cpp_Decoder_results_from_decode(XPtr<std::vector<DecodeResult>> obj) {
  std::vector<DecodeResult> *out(obj);
  std::vector<double> score_vec;
  std::vector<double> emittingModelScore_vec;
  std::vector<double> lmScore_vec;
  std::vector<std::vector<int>> words_vec;
  std::vector<std::vector<int>> tokens_vec;
  
  for (auto const& it : *out) {
    score_vec.push_back(it.score);
    emittingModelScore_vec.push_back(it.emittingModelScore);
    lmScore_vec.push_back(it.lmScore);
    words_vec.push_back(it.words);
    tokens_vec.push_back(it.tokens);
  }
  
  return Rcpp::List::create(
    Rcpp::Named("score") = score_vec,
    Rcpp::Named("emittingModelScore") = emittingModelScore_vec,
    Rcpp::Named("lmScore") = lmScore_vec,
    Rcpp::Named("words") = words_vec,
    Rcpp::Named("tokens") = tokens_vec
  );
}

// [[Rcpp::export]]
Rcpp::List cpp_Decoder_decode_numeric_vector(XPtr<Decoder> obj, std::vector<float>& emissions, int T, int N) {
  float *emissions_ = emissions.data();
  std::vector<DecodeResult> *out = new std::vector<DecodeResult>(obj->decode(emissions_, T, N));
  XPtr<std::vector<DecodeResult>> out_ptr(out, true);
  return cpp_Decoder_results_from_decode(out_ptr);
}

// [[Rcpp::export]]
Rcpp::List cpp_Decoder_decode_numeric_ptr(XPtr<Decoder> obj, int64_t emissions, int T, int N) {
  float* emissions_ = reinterpret_cast<float*>(emissions);
  std::vector<DecodeResult> *out = new std::vector<DecodeResult>(obj->decode(emissions_, T, N));
  XPtr<std::vector<DecodeResult>> out_ptr(out, true);
  return cpp_Decoder_results_from_decode(out_ptr);
}

// [[Rcpp::export]]
void cpp_Decoder_prune(XPtr<Decoder> obj, int lookBack = 0) {
  obj->prune(lookBack);
}

// [[Rcpp::export]]
int cpp_Decoder_nDecodedFramesInBuffer(XPtr<Decoder> obj) {
  return obj->nDecodedFramesInBuffer();
}

// [[Rcpp::export]]
Rcpp::List cpp_Decoder_getBestHypothesis(XPtr<Decoder> obj, int lookBack = 0) {
  // DecodeResult *out = new DecodeResult();
  // *out = obj->getBestHypothesis(lookBack);
  // XPtr<DecodeResult> out_ptr(out, true);

  // std::vector<DecodeResult>* out;
  // out->push_back(obj->getBestHypothesis(lookBack));
  // XPtr<std::vector<DecodeResult>> out_ptr(out, true);
  
  
  std::vector<DecodeResult>* out = new std::vector<DecodeResult>({obj->getBestHypothesis(lookBack)});
  XPtr<std::vector<DecodeResult>> out_ptr(out, true);

  return cpp_Decoder_results_from_decode(out_ptr);
}

// [[Rcpp::export]]
Rcpp::List cpp_Decoder_getAllFinalHypothesis(XPtr<Decoder> obj) {
  std::vector<DecodeResult>* out = new std::vector<DecodeResult>(obj->getAllFinalHypothesis());
  XPtr<std::vector<DecodeResult>> out_ptr(out, true);
  return cpp_Decoder_results_from_decode(out_ptr);
}

