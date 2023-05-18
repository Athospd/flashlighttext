
#include <Rcpp.h>
// [[Rcpp::plugins(cpp11)]]

#include <string>
using namespace Rcpp;
#include <flashlight/lib/text/decoder/lm/LM.h>
#include <flashlight/lib/text/dictionary/Dictionary.h>
#include <flashlight/lib/text/dictionary/Utils.h>
#include "wrappers.h"
using namespace fl::lib::text;

// methods ------------------------------
// [[Rcpp::export]]
XPtr<LMStateWrapper> cpp_LMWrapper_start(XPtr<LMWrapper> obj, bool startWithNothing) {
  LMStateWrapper* lm_state_ptr = new LMStateWrapper(obj->getLMWrap()->start(startWithNothing));
  XPtr<LMStateWrapper> out(lm_state_ptr, true);
  return out;
}

// [[Rcpp::export]]
Rcpp::List cpp_LMWrapper_score(XPtr<LMWrapper> obj, XPtr<LMStateWrapper> state, const int usrTokenIdx) {
  
  std::pair<LMStatePtr, float> score = obj->getLMWrap()->score(state->getLMStateWrap(), usrTokenIdx);
  auto score_state = new LMStateWrapper(score.first);
  
  Rcpp::List out = Rcpp::List::create(
    Rcpp::Named("state") = XPtr<LMStateWrapper>(score_state),
    Rcpp::Named("score") = score.second
  );
  
  return out;
}

// [[Rcpp::export]]
Rcpp::List cpp_LMWrapper_finish(XPtr<LMWrapper> obj, XPtr<LMStateWrapper> state) {
  
  std::pair<LMStatePtr, float> finish = obj->getLMWrap()->finish(state->getLMStateWrap());
  auto finish_state = new LMStateWrapper(finish.first);
  
  List out = Rcpp::List::create(
    Rcpp::Named("state") = XPtr<LMStateWrapper>(finish_state),
    Rcpp::Named("score") = finish.second
  );
  
  return out;
}

