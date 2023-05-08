#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::export]]
void test(int& x) {
  int p = x;
  int a = x;
  
  std::cout << "x: " << x << std::endl;
  std::cout << "*p: " << *p << std::endl;
  std::cout << "p: " << p << std::endl;
  std::cout << "a: " << a << std::endl;
  std::cout << "*a: " << *a << std::endl;
}

/*** R
test(42)
*/
