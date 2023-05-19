
#include <Rcpp.h>
using namespace Rcpp;
#include <flashlight/lib/text/decoder/Utils.h>
#include "wrappers.h"
using namespace fl::lib::text;

// // EmittingModelUpdateFunc //////////////////////////////////////////////////////
// // constructors ------------------------------
// // [[Rcpp::export]]
// XPtr<EmittingModelUpdateFunc> cpp_EmittingModelUpdateFunc_constructor(
//     const float* emissions,
//     int& N,
//     int& T,
//     std::vector<int>& last_token_ids,
//     std::vector<int>& proposed_token_ids,
//     std::vector<EmittingModelStatePtr>& previous_states,
//     int& current_time_step
// ) {
//   EmittingModelUpdateFunc* obj = new EmittingModelUpdateFunc();
//   XPtr<EmittingModelUpdateFunc> ptr(obj, true);
//   return ptr;
// }


// methods ------------------------------

//https://github.com/flashlight/text/blob/7cba9a1351eba52727bc2948a66c62cb75ca60d1/flashlight/lib/text/decoder/Utils.h




// 
// 
// EmittingModelUpdateFunc = std::function<
//   std::pair<
//     std::vector<std::vector<float>>,
//     std::vector<EmittingModelStatePtr>
//   > (
//       const float*,
//       const int,
//       const int,
//       const std::vector<int>&,
//       const std::vector<int>&,
//       const std::vector<EmittingModelStatePtr>&,
//       int&
//   )
// >
