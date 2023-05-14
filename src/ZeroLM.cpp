
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
XPtr<LMStatePtr> cpp_ZeroLMWrapper_start(XPtr<ZeroLMWrapper> obj, bool startWithNothing) {
  auto lm_state_ptr = new LMStatePtr();
  *lm_state_ptr = obj->zerolm_wrap->start(startWithNothing);
  XPtr<LMStatePtr> out(lm_state_ptr, true);
  return out;
}

// [[Rcpp::export]]
List cpp_ZeroLMWrapper_score(XPtr<ZeroLMWrapper> obj, XPtr<LMStatePtr> state, const int usrTozeroIdx) {
  
  std::pair<LMStatePtr, float> score = obj->zerolm_wrap->score(*state.get(), usrTozeroIdx);
  auto score_state = new LMStatePtr();
  *score_state = score.first;
  
  List out = Rcpp::List::create(
    Rcpp::Named("state") = XPtr<LMStatePtr>(score_state),
    Rcpp::Named("score") = score.second
  );
  
  return out;
}

// [[Rcpp::export]]
Rcpp::List cpp_ZeroLMWrapper_finish(XPtr<ZeroLMWrapper> obj, XPtr<LMStatePtr> state) {
  
  std::pair<LMStatePtr, float> finish = obj->zerolm_wrap->finish(*state.get());
  auto finish_state = new LMStatePtr();
  *finish_state = finish.first;
  
  Rcpp::List out = Rcpp::List::create(
    Rcpp::Named("state") = XPtr<LMStatePtr>(finish_state),
    Rcpp::Named("score") = finish.second
  );
  
  return out;
}
