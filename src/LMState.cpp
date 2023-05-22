#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <Rcpp.h>
// [[Rcpp::plugins(cpp11)]]
using namespace Rcpp;
#include <flashlight/lib/text/decoder/lm/LM.h>
#include <flashlight/lib/text/dictionary/Dictionary.h>
#include <flashlight/lib/text/dictionary/Utils.h>
#include "wrappers.h"
using namespace fl::lib::text;

// constructors ------------------------------
// [[Rcpp::export]]
XPtr<LMStateWrapper> cpp_LMStateWrapper_constructor() {
  LMStateWrapper *obj = new LMStateWrapper();
  XPtr<LMStateWrapper> obj_ptr(obj, true);
  return obj_ptr;
}

// methods ------------------------------
// [[Rcpp::export]]
XPtr<LMStateWrapper> cpp_LMStateWrapper_child(XPtr<LMStateWrapper> obj, int& usrIdx) {
  auto lm_state_ptr = new LMStateWrapper(obj->getLMStateWrap()->child<LMState>(usrIdx));
  XPtr<LMStateWrapper> out(lm_state_ptr, true);
  return out;
}

// TO DO
// // [[Rcpp::export]]
// Rcpp::List cpp_LMStateWrapper_child_as_r(XPtr<LMStateWrapper> obj, int& usrIdx) {
//   auto lm_state_ptr = new LMStateWrapper(obj->getLMStateWrap()->child<LMState>(usrIdx));
//   XPtr<LMStateWrapper> out(lm_state_ptr, true);
//   return out;
// }

// [[Rcpp::export]]
int cpp_LMStateWrapper_compare(XPtr<LMStateWrapper> obj, XPtr<LMStateWrapper> state) {
  return obj->getLMStateWrap()->compare(state->getLMStateWrap());
}

typedef int Key;
typedef LMState Value;

// [[Rcpp::export]]
Rcpp::List cpp_LMStateWrapper_children(XPtr<LMStateWrapper> obj) {
  
  std::unordered_map<int, LMStatePtr> children = obj->getLMStateWrap()->children;
  std::vector<int> indices;
  std::vector<XPtr<LMStateWrapper>> lm_states;
  
  for (auto& child : children) {
    auto lm_state_ptr = new LMStateWrapper(child.second);
    
    indices.push_back(child.first);
    lm_states.push_back(XPtr<LMStateWrapper>(lm_state_ptr)); //
  }
  
  // further reshaping towards a named list is done on the R side.
  List output = Rcpp::List::create(
    Rcpp::Named("indice") = indices,//keys,
    Rcpp::Named("lm_state") = lm_states//values
  );
  return output;
}

