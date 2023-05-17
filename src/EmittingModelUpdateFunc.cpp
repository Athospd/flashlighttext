
#include <Rcpp.h>
using namespace Rcpp;
#include <flashlight/lib/text/decoder/Utils.h>
#include "wrappers.h"
using namespace fl::lib::text;

// EmittingModelUpdateFunc //////////////////////////////////////////////////////
// constructors ------------------------------
// [[Rcpp::export]]
XPtr<EmittingModelUpdateFunc> cpp_EmittingModelUpdateFunc_constructor(
    
) {
  EmittingModelUpdateFunc* obj = new EmittingModelUpdateFunc();
  XPtr<EmittingModelUpdateFunc> ptr(obj, true);
  return ptr;
}


// methods ------------------------------

//https://github.com/flashlight/text/blob/7cba9a1351eba52727bc2948a66c62cb75ca60d1/flashlight/lib/text/decoder/Utils.h