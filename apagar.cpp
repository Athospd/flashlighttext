#include <Rcpp.h>
#include <memory>
using namespace Rcpp;

// A simple class for testing ----------------------------
class A{
public:
  int value;
  A(int x);
};
A::A(int x) {this->value = x + 10;}

using APtr = std::shared_ptr<A>;

class AWrapper{
public:
  APtr a_wrap;
  AWrapper(int x): a_wrap(std::make_shared<A>(x)){};
};

// The regular way to access an instance of a class using XPtr ----------------------------
// Everything is fine here, nothing to do.
// [[Rcpp::export]]
XPtr<A> A_constructor(int x) {
  A *a = new A(x);
  XPtr<A> out(a, true);
  return out;
}

// [[Rcpp::export]]
int A_test(XPtr<A> x) {
  return x->value;
}

// THE PROBLEM ----------------------------
// A given C++ lib expect to receive an shared_ptr instead of a class instance itself.
// [[Rcpp::export]]
XPtr<APtr> APtr_constructor(int x) {
  APtr a = std::make_shared<A>(x);
  std::cout << a->value << std::endl;
  XPtr<APtr> out_ptr(&a, true); // <--------------- how do I wrap 'a' here??
  return out_ptr;
}

// [[Rcpp::export]]
int APtr_test(XPtr<APtr> x) {
  return x->get()->value; // <--------------- how do I access the A instance pointed by APtr x (which was wrapped by XPtr)?
}

// Wrapper solution ----------------------------
// Using an auxiliary class to store a APtr and the XPtr an instance of it.
// [[Rcpp::export]]
XPtr<AWrapper> AWrapper_constructor(int x) {
  AWrapper *a_w = new AWrapper(x);
  XPtr<AWrapper> out_ptr(a_w, true);
  return out_ptr;
}

// [[Rcpp::export]]
int AWrapper_test(XPtr<AWrapper> x) {
  return x->a_wrap->value; 
}

/*** R
# Working correctly ------------------------------------
a <- A_constructor(42)
A_test(a)

# NOT working ------------------------------------------
a_ptr <- APtr_constructor(42)
APtr_test(a_ptr)

# working ------------------------------------------
a_w <- AWrapper_constructor(42)
AWrapper_test(a_w)
*/