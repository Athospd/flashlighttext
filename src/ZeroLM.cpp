
#include <Rcpp.h>
// [[Rcpp::plugins(cpp11)]]

#include <string>
using namespace Rcpp;
#include <flashlight/lib/text/decoder/lm/ZeroLM.h>
#include <flashlight/lib/text/dictionary/Dictionary.h>
#include <flashlight/lib/text/dictionary/Utils.h>
#include "wrappers.h"
using namespace fl::lib::text;

// constructors ------------------------------
// [[Rcpp::export]]
XPtr<ZeroLMWrapper> cpp_ZeroLMWrapper_constructor() {
  ZeroLMWrapper *obj = new ZeroLMWrapper();
  XPtr<ZeroLMWrapper> obj_ptr(obj, true);
  return obj_ptr;
}

// methods ------------------------------
// [[Rcpp::export]]
XPtr<LMStateWrapper> cpp_ZeroLMWrapper_start(XPtr<ZeroLMWrapper> obj, bool startWithNothing) {
  LMStateWrapper* lm_state_ptr = new LMStateWrapper(obj->getZeroLMWrap()->start(startWithNothing));
  XPtr<LMStateWrapper> out(lm_state_ptr, true);
  return out;
}

// [[Rcpp::export]]
Rcpp::List cpp_ZeroLMWrapper_score(XPtr<ZeroLMWrapper> obj, XPtr<LMStateWrapper> state, const int usrTozeroIdx) {
  
  std::pair<LMStatePtr, float> score = obj->getZeroLMWrap()->score(state->getLMStateWrap(), usrTozeroIdx);
  auto score_state = new LMStateWrapper(score.first);
  
  List out = Rcpp::List::create(
    Rcpp::Named("state") = XPtr<LMStateWrapper>(score_state),
    Rcpp::Named("score") = score.second
  );
  
  return out;
}

// [[Rcpp::export]]
Rcpp::List cpp_ZeroLMWrapper_finish(XPtr<ZeroLMWrapper> obj, XPtr<LMStateWrapper> state) {
  
  std::pair<LMStatePtr, float> finish = obj->getZeroLMWrap()->finish(state->getLMStateWrap());
  auto finish_state = new LMStateWrapper(finish.first);
  
  Rcpp::List out = Rcpp::List::create(
    Rcpp::Named("state") = XPtr<LMStateWrapper>(finish_state),
    Rcpp::Named("score") = finish.second
  );
  
  return out;
}
