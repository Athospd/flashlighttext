
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

// methods ------------------------------
// [[Rcpp::export]]
XPtr<LMStatePtr> cpp_KenLM_start(XPtr<KenLM> obj, bool startWithNothing) {
  auto lm_state_ptr = new LMStatePtr();
  *lm_state_ptr = obj->start(startWithNothing);
  XPtr<LMStatePtr> out(lm_state_ptr, true);
  return out;
}

// [[Rcpp::export]]
List cpp_KenLM_score(XPtr<KenLM> obj, XPtr<LMStatePtr> state, const int usrTokenIdx) {
  
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
List cpp_KenLM_finish(XPtr<KenLM> obj, XPtr<LMStatePtr> state) {
  
  std::pair<LMStatePtr, float> finish = obj->finish(*state.get());
  auto finish_state = new LMStatePtr();
  *finish_state = finish.first;
  
  List out = Rcpp::List::create(
    Rcpp::Named("state") = XPtr<LMStatePtr>(finish_state),
    Rcpp::Named("score") = finish.second
  );
  
  return out;
}
