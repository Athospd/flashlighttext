
#include <Rcpp.h>
// [[Rcpp::plugins(cpp11)]]

#include <string>
using namespace Rcpp;
#include <flashlight/lib/text/decoder/lm/KenLM.h>
#include <flashlight/lib/text/dictionary/Dictionary.h>
#include <flashlight/lib/text/dictionary/Utils.h>
#include "wrappers.h"
using namespace fl::lib::text;

// constructors ------------------------------
// [[Rcpp::export]]
XPtr<KenLMWrapper> cpp_KenLMWrapper_constructor(const std::string& path, XPtr<Dictionary> usrTknDict) {
  KenLMWrapper *obj = new KenLMWrapper(path, *usrTknDict.get());
  XPtr<KenLMWrapper> obj_ptr(obj, true);
  return obj_ptr;
}

// methods ------------------------------
// [[Rcpp::export]]
XPtr<LMStateWrapper> cpp_KenLMWrapper_start(XPtr<KenLMWrapper> obj, bool startWithNothing) {
  LMStateWrapper* lm_state_ptr = new LMStateWrapper(obj->getKenLMWrap()->start(startWithNothing));
  XPtr<LMStateWrapper> out(lm_state_ptr, true);
  return out;
}

// [[Rcpp::export]]
List cpp_KenLMWrapper_score(XPtr<KenLMWrapper> obj, XPtr<LMStateWrapper> state, const int usrTokenIdx) {
  
  std::pair<LMStatePtr, float> score = obj->getKenLMWrap()->score(state->getLMStateWrap(), usrTokenIdx);
  auto score_state = new LMStateWrapper(score.first);
  
  List out = Rcpp::List::create(
    Rcpp::Named("state") = XPtr<LMStateWrapper>(score_state),
    Rcpp::Named("score") = score.second
  );
  
  return out;
}

// [[Rcpp::export]]
Rcpp::List cpp_KenLMWrapper_finish(XPtr<KenLMWrapper> obj, XPtr<LMStateWrapper> state) {
  
  std::pair<LMStatePtr, float> finish = obj->getKenLMWrap()->finish(state->getLMStateWrap());
  auto finish_state = new LMStateWrapper(finish.first);
  
  List out = Rcpp::List::create(
    Rcpp::Named("state") = XPtr<LMStateWrapper>(finish_state),
    Rcpp::Named("score") = finish.second
  );
  
  return out;
}
