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
XPtr<Decoder> cpp_LexiconFreeDecoder_constructor(
    XPtr<LexiconFreeDecoderOptions> opt,
    XPtr<LMWrapper> lm,
    int sil,
    int blank,
    std::vector<float>& transitions
) {
  LexiconFreeDecoderOptions opt_ = *opt;
  Decoder *decoder = new LexiconFreeDecoder(
  opt_,
  lm->getLMWrap(), 
  sil, 
  blank,
  transitions
  );
  
  XPtr<Decoder> ptr(decoder, true);
  return ptr;
}

// methods ------------------------------
// [[Rcpp::export]]
int cpp_LexiconFreeDecoder_nHypothesis(XPtr<LexiconFreeDecoder> obj) {
  return obj->nHypothesis();
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
    Rcpp::Named("beam_size_token") = opt.beamSizeToken, 
    Rcpp::Named("beam_threshold") = opt.beamThreshold,
    Rcpp::Named("lm_weight") = opt.lmWeight, 
    Rcpp::Named("sil_score") = opt.silScore,
    Rcpp::Named("log_add") = opt.logAdd, 
    Rcpp::Named("criterion_type") = CriterionType_to_string2(opt.criterionType)
  );
}

// [[Rcpp::export]]
std::vector<float> cpp_LexiconFreeDecoder_getTransitions(XPtr<LexiconFreeDecoder> obj) {
  return obj->getTransitions();
}

