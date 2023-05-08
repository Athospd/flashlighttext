#include <stdexcept>
#include <Rcpp.h>
#include <string>
using namespace Rcpp;
#include <flashlight/lib/text/decoder/LexiconDecoder.h>
using namespace fl::lib::text;

CriterionType string_to_CriterionType(std::string& criterion_type) {
  if(criterion_type == "ASG") return CriterionType::ASG;
  else if(criterion_type == "CTC") return CriterionType::CTC;
  else if(criterion_type == "S2S") return CriterionType::S2S;
  throw std::invalid_argument("criterion_type should be one of CTC, ASG, or S2S");
}

std::string CriterionType_to_string(CriterionType& criterion_type) {
  if(criterion_type == CriterionType::ASG) return "ASG";
  else if(criterion_type == CriterionType::CTC) return "CTC";
  else if(criterion_type == CriterionType::S2S) return "S2S";
  throw std::invalid_argument("criterion_type should be one of CTC, ASG, or S2S");
}

// constructors ------------------------------
// [[Rcpp::export]]
XPtr<LexiconDecoderOptions> cpp_LexiconDecoderOptions_constructor(
  int& beamSize, // Maximum number of hypothesis we hold after each step
  int& beamSizeToken, // Maximum number of tokens we consider at each step
  double& beamThreshold, // Threshold to prune hypothesis
  double& lmWeight, // Weight of lm
  double& wordScore, // Word insertion score
  double& unkScore, // Unknown word insertion score
  double& silScore, // Silence insertion score
  bool& logAdd, // If or not use logadd when merging hypothesis
  std::string& criterionType // CTC or ASG
) {
  LexiconDecoderOptions* obj = new LexiconDecoderOptions;
  *obj = {
    beamSize,
    beamSizeToken,
    beamThreshold,
    lmWeight,
    wordScore,
    unkScore,
    silScore,
    logAdd,
    string_to_CriterionType(criterionType)
  };
  XPtr<LexiconDecoderOptions> ptr(obj, true);
  return ptr;
}

// [[Rcpp::export]]
void cpp_LexiconDecoderOptions_set_beamSize(XPtr<LexiconDecoderOptions> obj, int value) {obj->beamSize = value;}
// [[Rcpp::export]]
int cpp_LexiconDecoderOptions_get_beamSize(XPtr<LexiconDecoderOptions> obj) {return obj->beamSize;}
// [[Rcpp::export]]
void cpp_LexiconDecoderOptions_set_beamSizeToken(XPtr<LexiconDecoderOptions> obj, int value) {obj->beamSizeToken = value;}
// [[Rcpp::export]]
int cpp_LexiconDecoderOptions_get_beamSizeToken(XPtr<LexiconDecoderOptions> obj) {return obj->beamSizeToken;}
// [[Rcpp::export]]
void cpp_LexiconDecoderOptions_set_beamThreshold(XPtr<LexiconDecoderOptions> obj, double value) {obj->beamThreshold = value;}
// [[Rcpp::export]]
double cpp_LexiconDecoderOptions_get_beamThreshold(XPtr<LexiconDecoderOptions> obj) {return obj->beamThreshold;}
// [[Rcpp::export]]
void cpp_LexiconDecoderOptions_set_lmWeight(XPtr<LexiconDecoderOptions> obj, double value) {obj->lmWeight = value;}
// [[Rcpp::export]]
double cpp_LexiconDecoderOptions_get_lmWeight(XPtr<LexiconDecoderOptions> obj) {return obj->lmWeight;}
// [[Rcpp::export]]
void cpp_LexiconDecoderOptions_set_wordScore(XPtr<LexiconDecoderOptions> obj, double value) {obj->wordScore = value;}
// [[Rcpp::export]]
double cpp_LexiconDecoderOptions_get_wordScore(XPtr<LexiconDecoderOptions> obj) {return obj->wordScore;}
// [[Rcpp::export]]
void cpp_LexiconDecoderOptions_set_unkScore(XPtr<LexiconDecoderOptions> obj, double value) {obj->unkScore = value;}
// [[Rcpp::export]]
double cpp_LexiconDecoderOptions_get_unkScore(XPtr<LexiconDecoderOptions> obj) {return obj->unkScore;}
// [[Rcpp::export]]
void cpp_LexiconDecoderOptions_set_silScore(XPtr<LexiconDecoderOptions> obj, double value) {obj->silScore = value;}
// [[Rcpp::export]]
double cpp_LexiconDecoderOptions_get_silScore(XPtr<LexiconDecoderOptions> obj) {return obj->silScore;}
// [[Rcpp::export]]
void cpp_LexiconDecoderOptions_set_logAdd(XPtr<LexiconDecoderOptions> obj, bool value) {obj->logAdd = value;}
// [[Rcpp::export]]
bool cpp_LexiconDecoderOptions_get_logAdd(XPtr<LexiconDecoderOptions> obj) {return obj->logAdd;}
// [[Rcpp::export]]
void cpp_LexiconDecoderOptions_set_CriterionType(XPtr<LexiconDecoderOptions> obj, std::string value) {obj->criterionType = string_to_CriterionType(value);}
// [[Rcpp::export]]
std::string cpp_LexiconDecoderOptions_get_CriterionType(XPtr<LexiconDecoderOptions> obj) {return CriterionType_to_string(obj->criterionType);}
