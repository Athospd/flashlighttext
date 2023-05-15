#include <stdexcept>
#include <Rcpp.h>
#include <string>
using namespace Rcpp;
#include <flashlight/lib/text/decoder/Trie.h>
#include "wrappers.h"
using namespace fl::lib::text;

// Trie ////////////////////////////////////////////////////////////////////
// constructors ------------------------------
// [[Rcpp::export]]
XPtr<TrieWrapper> cpp_TrieWrapper_constructor(int maxChildren, int rootIdx) {
  TrieWrapper *obj = new TrieWrapper(maxChildren, rootIdx);
  XPtr<TrieWrapper> ptr(obj, true);
  return ptr;
}

// methods ------------------------------
// [[Rcpp::export]]
XPtr<TrieNode> cpp_TrieWrapper_getRoot(XPtr<TrieWrapper> obj) {
  auto trie_node = new TrieNode(0L);
  *trie_node = *(obj->getTrieWrap()->getRoot());
  XPtr<TrieNode> out(trie_node, true);
  return out;
}

// [[Rcpp::export]]
XPtr<TrieNodeWrapper> cpp_TrieWrapper_insert(XPtr<TrieWrapper> obj, const std::vector<int>& indices, int label, float score) {
  auto trie_node_ptr = new TrieNodeWrapper(obj->getTrieWrap()->insert(indices, label, score));
  XPtr<TrieNodeWrapper> out(trie_node_ptr, true);
  return out;
}

// [[Rcpp::export]]
XPtr<TrieNodeWrapper> cpp_TrieWrapper_search(XPtr<TrieWrapper> obj, const std::vector<int>& indices) {
  auto trie_node_ptr = new TrieNodeWrapper(obj->getTrieWrap()->search(indices));
  XPtr<TrieNodeWrapper> out(trie_node_ptr, true);
  return out;
}

SmearingMode SmearingMode_convert(const std::string& smear_mode) {
  if(smear_mode == "NONE") return SmearingMode::NONE;
  else if(smear_mode == "MAX") return SmearingMode::MAX;
  else if(smear_mode == "LOGADD") return SmearingMode::LOGADD;
  throw std::invalid_argument("smear_mode should be one of NONE, MAX, or LOGADD");
}

// [[Rcpp::export]]
void cpp_TrieWrapper_smear(XPtr<TrieWrapper> obj, std::string& smear_mode) {
  SmearingMode smear_mode_ = SmearingMode_convert(smear_mode);
  obj->getTrieWrap()->smear(smear_mode_);
}




// TrieNode ////////////////////////////////////////////////////////////////
// constructors ------------------------------
// [[Rcpp::export]]
XPtr<TrieNode> cpp_TrieNode_constructor(int idx) {
  TrieNode *obj = new TrieNode(idx);
  XPtr<TrieNode> ptr(obj, true);
  return ptr;
}

// methods ------------------------------
// [[Rcpp::export]]
float cpp_TrieNode_maxScore(XPtr<TrieNodePtr> obj) {
  return obj->get()->maxScore;
}

