
#include <flashlight/lib/text/decoder/lm/KenLM.h>
#include <flashlight/lib/text/dictionary/Dictionary.h>
#include <Rcpp.h>
#include <string>
using namespace Rcpp;
using namespace fl::lib::text;

// constructors ------------------------------
// [[Rcpp::export]]
void cpp_KenLM_constructor(const std::string& path, SEXP ptr) {
  // KenLM(const std::string& path, const Dictionary& usrTknDict);

  Dictionary usrTknDict;
  std::shared_ptr<KenLM> obj = std::make_shared<KenLM>(path, usrTknDict);
}



// Rcpp::XPtr<KenLM> ptr2(obj.get(), true);
// KenLM obj;
// const Rcpp::XPtr<Dictionary> usrTknDict(ptr);
// std::shared_ptr<Dictionary> usrTknDict = std::make_shared<Dictionary>();
// KenLM obj = new KenLM(path, usrTknDict);