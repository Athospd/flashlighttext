
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
XPtr<KenLM> cpp_KenLM_constructor(const std::string& path, SEXP ptr) {
  Dictionary usrTknDict = *XPtr<Dictionary>(ptr);
  KenLM *obj = new KenLM(path, usrTknDict);
  XPtr<KenLM> obj_ptr(obj, true);
  return obj_ptr;
}

// [[Rcpp::export]]
XPtr<KenLMWrapper> cpp_KenLMWrapper_constructor(const std::string& path, SEXP ptr) {
  Dictionary usrTknDict = *XPtr<Dictionary>(ptr);
  KenLMWrapper *obj = new KenLMWrapper(path, usrTknDict);
  XPtr<KenLMWrapper> obj_ptr(obj, true);
  return obj_ptr;
}

// methods ------------------------------
// [[Rcpp::export]]
XPtr<LMStatePtr> cpp_KenLM_start(XPtr<LM> obj, bool startWithNothing) {
  auto lm_state_ptr = new LMStatePtr();
  *lm_state_ptr = obj->start(startWithNothing);
  XPtr<LMStatePtr> out(lm_state_ptr, true);
  return out;
}

// [[Rcpp::export]]
XPtr<LMStatePtr> cpp_KenLMWrapper_start(XPtr<KenLMWrapper> obj, bool startWithNothing) {
  auto lm_state_ptr = new LMStatePtr();
  *lm_state_ptr = obj->kenlm_wrap->start(startWithNothing);
  XPtr<LMStatePtr> out(lm_state_ptr, true);
  return out;
}

// [[Rcpp::export]]
List cpp_KenLM_score(XPtr<LM> obj, XPtr<LMStatePtr> state, const int usrTokenIdx) {
  
  std::pair<LMStatePtr, float> score = obj->score(*state.get(), usrTokenIdx);
  auto score_state = new LMStatePtr();
  *score_state = score.first;
  
  List out = Rcpp::List::create(
    Rcpp::Named("state") = XPtr<LMStatePtr>(score_state),
    Rcpp::Named("score") = score.second
  );
  
  return out;
}

// [[Rcpp::export]]
List cpp_KenLMWrapper_score(XPtr<KenLMWrapper> obj, XPtr<LMStatePtr> state, const int usrTokenIdx) {
  
  std::pair<LMStatePtr, float> score = obj->kenlm_wrap->score(*state.get(), usrTokenIdx);
  auto score_state = new LMStatePtr();
  *score_state = score.first;
  
  List out = Rcpp::List::create(
    Rcpp::Named("state") = XPtr<LMStatePtr>(score_state),
    Rcpp::Named("score") = score.second
  );
  
  return out;
}

// [[Rcpp::export]]
List cpp_KenLM_finish(XPtr<LM> obj, XPtr<LMStatePtr> state) {
  
  std::pair<LMStatePtr, float> finish = obj->finish(*state.get());
  auto finish_state = new LMStatePtr();
  *finish_state = finish.first;
  
  List out = Rcpp::List::create(
    Rcpp::Named("state") = XPtr<LMStatePtr>(finish_state),
    Rcpp::Named("score") = finish.second
  );
  
  return out;
}

// [[Rcpp::export]]
Rcpp::List cpp_KenLMWrapper_finish(XPtr<KenLMWrapper> obj, XPtr<LMStatePtr> state) {
  
  std::pair<LMStatePtr, float> finish = obj->kenlm_wrap->finish(*state.get());
  auto finish_state = new LMStatePtr();
  *finish_state = finish.first;
  
  Rcpp::List out = Rcpp::List::create(
    Rcpp::Named("state") = XPtr<LMStatePtr>(finish_state),
    Rcpp::Named("score") = finish.second
  );
  
  return out;
}
