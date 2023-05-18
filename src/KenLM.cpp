
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
XPtr<LMWrapper> cpp_KenLMWrapper_constructor(const std::string& path, XPtr<Dictionary> usrTknDict) {
  LMWrapper *obj = new KenLMWrapper(path, *usrTknDict.get());
  XPtr<LMWrapper> obj_ptr(obj, true);
  return obj_ptr;
}

