#include <stdexcept>
#include <Rcpp.h>
#include <string>
#include <fstream>
#include <iostream>
using namespace Rcpp;
#include <flashlight/lib/text/decoder/LexiconFreeDecoder.h>
#include <flashlight/lib/text/dictionary/Utils.h>
#include <flashlight/lib/text/dictionary/Dictionary.h>
#include <flashlight/lib/text/decoder/lm/LM.h>
#include <flashlight/lib/text/decoder/lm/KenLM.h>
#include <flashlight/lib/text/decoder/Trie.h>
#include "wrappers.h"
using namespace fl::lib::text;

CriterionType string_to_CriterionType2(std::string& criterion_type) {
  if(criterion_type == "ASG") return CriterionType::ASG;
  else if(criterion_type == "CTC") return CriterionType::CTC;
  else if(criterion_type == "S2S") return CriterionType::S2S;
  throw std::invalid_argument("criterion_type should be one of CTC, ASG, or S2S");
}

std::string CriterionType_to_string2(CriterionType& criterion_type) {
  if(criterion_type == CriterionType::ASG) return "ASG";
  else if(criterion_type == CriterionType::CTC) return "CTC";
  else if(criterion_type == CriterionType::S2S) return "S2S";
  throw std::invalid_argument("criterion_type should be one of CTC, ASG, or S2S");
}

// LexiconFreeDecoderOptions //////////////////////////////////////////////////////
// constructors ------------------------------
// [[Rcpp::export]]
XPtr<LexiconFreeDecoderOptions> cpp_LexiconFreeDecoderOptions_constructor(
    int& beamSize, // Maximum number of hypothesis we hold after each step
    int& beamSizeToken, // Maximum number of tokens we consider at each step
    double& beamThreshold, // Threshold to prune hypothesis
    double& lmWeight, // Weight of lm
    double& silScore, // Silence insertion score
    bool& logAdd, // If or not use logadd when merging hypothesis
    std::string& criterionType // CTC or ASG
) {
  LexiconFreeDecoderOptions* obj = new LexiconFreeDecoderOptions;
  *obj = {
    beamSize,
    beamSizeToken,
    beamThreshold,
    lmWeight,
    silScore,
    logAdd,
    string_to_CriterionType2(criterionType)
  };
  XPtr<LexiconFreeDecoderOptions> ptr(obj, true);
  return ptr;
}

// methods ------------------------------
// [[Rcpp::export]]
void cpp_LexiconFreeDecoderOptions_set_beamSize(XPtr<LexiconFreeDecoderOptions> obj, int value) {obj->beamSize = value;}
// [[Rcpp::export]]
int cpp_LexiconFreeDecoderOptions_get_beamSize(XPtr<LexiconFreeDecoderOptions> obj) {return obj->beamSize;}
// [[Rcpp::export]]
void cpp_LexiconFreeDecoderOptions_set_beamSizeToken(XPtr<LexiconFreeDecoderOptions> obj, int value) {obj->beamSizeToken = value;}
// [[Rcpp::export]]
int cpp_LexiconFreeDecoderOptions_get_beamSizeToken(XPtr<LexiconFreeDecoderOptions> obj) {return obj->beamSizeToken;}
// [[Rcpp::export]]
void cpp_LexiconFreeDecoderOptions_set_beamThreshold(XPtr<LexiconFreeDecoderOptions> obj, double value) {obj->beamThreshold = value;}
// [[Rcpp::export]]
double cpp_LexiconFreeDecoderOptions_get_beamThreshold(XPtr<LexiconFreeDecoderOptions> obj) {return obj->beamThreshold;}
// [[Rcpp::export]]
void cpp_LexiconFreeDecoderOptions_set_lmWeight(XPtr<LexiconFreeDecoderOptions> obj, double value) {obj->lmWeight = value;}
// [[Rcpp::export]]
double cpp_LexiconFreeDecoderOptions_get_lmWeight(XPtr<LexiconFreeDecoderOptions> obj) {return obj->lmWeight;}
// [[Rcpp::export]]
void cpp_LexiconFreeDecoderOptions_set_silScore(XPtr<LexiconFreeDecoderOptions> obj, double value) {obj->silScore = value;}
// [[Rcpp::export]]
double cpp_LexiconFreeDecoderOptions_get_silScore(XPtr<LexiconFreeDecoderOptions> obj) {return obj->silScore;}
// [[Rcpp::export]]
void cpp_LexiconFreeDecoderOptions_set_logAdd(XPtr<LexiconFreeDecoderOptions> obj, bool value) {obj->logAdd = value;}
// [[Rcpp::export]]
bool cpp_LexiconFreeDecoderOptions_get_logAdd(XPtr<LexiconFreeDecoderOptions> obj) {return obj->logAdd;}
// [[Rcpp::export]]
void cpp_LexiconFreeDecoderOptions_set_CriterionType(XPtr<LexiconFreeDecoderOptions> obj, std::string value) {obj->criterionType = string_to_CriterionType2(value);}
// [[Rcpp::export]]
std::string cpp_LexiconFreeDecoderOptions_get_CriterionType(XPtr<LexiconFreeDecoderOptions> obj) {return CriterionType_to_string2(obj->criterionType);}



// LexiconFreeDecoder /////////////////////////////////////////////////////////
// constructors ------------------------------
// [[Rcpp::export]]  
XPtr<LexiconFreeDecoder> cpp_LexiconFreeDecoder_constructor(
    XPtr<LexiconFreeDecoderOptions> opt,
    XPtr<KenLMWrapper> lm,
    int sil,
    int blank,
    std::vector<float>& transitions
) {
  LexiconFreeDecoderOptions opt_ = *opt;
  LexiconFreeDecoder *decoder = new LexiconFreeDecoder(
  opt_,
  lm->getKenLMWrap(), 
  sil, 
  blank,
  transitions
  );
  
  XPtr<LexiconFreeDecoder> ptr(decoder, true);
  return ptr;
}

// methods ------------------------------
// [[Rcpp::export]]
void cpp_LexiconFreeDecoder_decodeBegin(XPtr<LexiconFreeDecoder> obj) {
  obj->decodeBegin();
}

// [[Rcpp::export]]
void cpp_LexiconFreeDecoder_decodeStep(XPtr<LexiconFreeDecoder> obj, std::vector<float>& emissions, int T, int N) {
  float *emissions_ = emissions.data();
  obj->decodeStep(emissions_, T, N);
}

// [[Rcpp::export]]
void cpp_LexiconFreeDecoder_decodeEnd(XPtr<LexiconFreeDecoder> obj) {
  obj->decodeEnd();
}

// [[Rcpp::export]]
List cpp_LexiconFreeDecoder_results_from_decode(XPtr<std::vector<DecodeResult>> obj) {
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
Rcpp::List cpp_LexiconFreeDecoder_decode(XPtr<LexiconFreeDecoder> obj, std::vector<float>& emissions, int T, int N) {
  float *emissions_ = emissions.data();
  std::vector<DecodeResult> *out = new std::vector<DecodeResult>(obj->decode(emissions_, T, N));
  XPtr<std::vector<DecodeResult>> out_ptr(out, true);
  return cpp_LexiconFreeDecoder_results_from_decode(out_ptr);
}

// [[Rcpp::export]]
int cpp_LexiconFreeDecoder_nHypothesis(XPtr<LexiconFreeDecoder> obj) {
  return obj->nHypothesis();
}

// [[Rcpp::export]]
void cpp_LexiconFreeDecoder_prune(XPtr<LexiconFreeDecoder> obj, int lookBack = 0) {
  obj->prune(lookBack);
}

// [[Rcpp::export]]
int cpp_LexiconFreeDecoder_nDecodedFramesInBuffer(XPtr<LexiconFreeDecoder> obj) {
  return obj->nDecodedFramesInBuffer();
}

// [[Rcpp::export]]
XPtr<DecodeResult> cpp_LexiconFreeDecoder_getBestHypothesis(XPtr<LexiconFreeDecoder> obj, int lookBack = 0) {
  DecodeResult *out = new DecodeResult();
  *out = obj->getBestHypothesis(lookBack);
  XPtr<DecodeResult> out_ptr(out, true);
  return out_ptr;
}

// [[Rcpp::export]]
Rcpp::List cpp_LexiconFreeDecoder_getAllFinalHypothesis(XPtr<LexiconFreeDecoder> obj) {
  std::vector<DecodeResult> *out = new std::vector<DecodeResult>(obj->getAllFinalHypothesis());
  XPtr<std::vector<DecodeResult>> out_ptr(out, true);
  return cpp_LexiconFreeDecoder_results_from_decode(out_ptr);
}

// TO DO
// https://github.com/flashlight/text/blob/7cba9a1351eba52727bc2948a66c62cb75ca60d1/flashlight/lib/text/decoder/LexiconFreeDecoder.h
// const LMPtr& getLMPtr() const;
// // [[Rcpp::export]]
// const XPtr<ZeroLMWrapper> getLMPtr(XPtr<LexiconFreeDecoder> obj) {
//   auto zerolm = new ZeroLMWrapper(*(obj->getLMPtr()));
//   return XPtr<ZeroLMWrapper>(zerolm, true);
// }

// [[Rcpp::export]]
int cpp_LexiconFreeDecoder_getSilIdx(XPtr<LexiconFreeDecoder> obj) {
  return obj->getSilIdx();
}

// [[Rcpp::export]]
int cpp_LexiconFreeDecoder_getBlankIdx(XPtr<LexiconFreeDecoder> obj) {
  return obj->getBlankIdx();
}

// [[Rcpp::export]]
Rcpp::List cpp_LexiconFreeDecoder_cpp_getOptions(XPtr<LexiconFreeDecoder> obj) {
  LexiconFreeDecoderOptions opt = obj->getOptions();
  
  return Rcpp::List::create(
    Rcpp::Named("beam_size") = opt.beamSize, 
    Rcpp::Named("beam_size_token") = 1, 
    Rcpp::Named("beam_threshold") = 1,
    Rcpp::Named("lm_weight") = 1, 
    Rcpp::Named("sil_score") = 1,
    Rcpp::Named("log_add") = 1, 
    Rcpp::Named("criterion_type") = 1
  );
}

// [[Rcpp::export]]
std::vector<float> cpp_LexiconFreeDecoder_getTransitions(XPtr<LexiconFreeDecoder> obj) {
  return obj->getTransitions();
}

