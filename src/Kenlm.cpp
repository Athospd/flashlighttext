
#include <Rcpp.h>
// [[Rcpp::plugins(cpp11)]]
#include <string>
using namespace Rcpp;
#include <flashlight/lib/text/decoder/lm/KenLM.h>
#include <flashlight/lib/text/dictionary/Dictionary.h>
#include <flashlight/lib/text/dictionary/Utils.h>
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
void explore_kenlm(XPtr<KenLM> obj) {
  std::cout << obj << std::endl; 
  // std::cout << *obj << std::endl; 
  std::cout << &obj << std::endl;
}

// methods ------------------------------
// [[Rcpp::export]]
XPtr<LMStatePtr> cpp_KenLM_start(XPtr<KenLM> obj, bool startWithNothing) {
  LMStatePtr lm_state = obj->start(startWithNothing);
  XPtr<LMStatePtr> lm_state_ptr(lm_state.get(), true);
  return lm_state_ptr;
}

// using LMStatePtr = std::shared_ptr<LMState>;

// [[Rcpp::export]]
List cpp_KenLM_score(XPtr<KenLM> obj, XPtr<LMStatePtr> state, const int usrTokenIdx) {
  
  LMStatePtr state_ = *XPtr<LMStatePtr>(state);
  // LMStatePtr state__ = std::make_shared<LMState>(state_);
  std::pair<LMStatePtr, float> score = obj->score(state_, usrTokenIdx);

  // LMStatePtr state__ = *XPtr<LMStatePtr>(score.first);
  // XPtr<LMStatePtr> state___(&state__, true);

  // std::pair<XPtr<LMStatePtr>, float> out = std::pair(state_, score[1]);
  List out = Rcpp::List::create(
    Rcpp::Named("state") = 1,
    Rcpp::Named("score") = 2
  );
  return out;
}
