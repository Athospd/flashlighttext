
#include <flashlight/lib/text/decoder/lm/LM.h>
#include <flashlight/lib/text/decoder/lm/KenLM.h>
#include <flashlight/lib/text/decoder/lm/ZeroLM.h>
#include <flashlight/lib/text/decoder/Trie.h>
using namespace fl::lib::text;

using LMPtr = std::shared_ptr<LM>;
using LMStatePtr = std::shared_ptr<LMState>;
using KenLMPtr = std::shared_ptr<KenLM>;
using ZeroLMPtr = std::shared_ptr<ZeroLM>;
using TriePtr = std::shared_ptr<Trie>;

class KenLMWrapper {
public:
  KenLMWrapper(KenLMPtr& newKenLMWrap) {
    kenlm_wrap = newKenLMWrap;
  }
  
  KenLMWrapper(
    const std::string& path, 
    const Dictionary& usrTknDict
  ): kenlm_wrap(std::make_shared<KenLM>(path, usrTknDict)) {};
  
  KenLMPtr& getKenLMWrap() {
    return kenlm_wrap;
  }
  
  void setKenLMWrap(KenLMPtr newKenLMWrap) {
    kenlm_wrap = newKenLMWrap;
  }
  
private:
  KenLMPtr kenlm_wrap;
};

class ZeroLMWrapper {
public:
  ZeroLMWrapper(): zerolm_wrap(std::make_shared<ZeroLM>()) {};
  ZeroLMWrapper(ZeroLMPtr newZeroLMWrap) {
    zerolm_wrap = newZeroLMWrap;
  };
  
  ZeroLMPtr& getZeroLMWrap() {
    return zerolm_wrap;
  }
  
  void setZeroLMWrap(ZeroLMPtr newZeroLMWrap) {
    zerolm_wrap = newZeroLMWrap;
  }
  
private:
  ZeroLMPtr zerolm_wrap;
};

class LMStateWrapper {
public:
  LMStateWrapper(): lmstate_wrap(std::make_shared<LMState>()) {};
  LMStateWrapper(LMStatePtr newLMStateWrap) {
    lmstate_wrap = newLMStateWrap;
  };
  
  LMStatePtr& getLMStateWrap() {
    return lmstate_wrap;
  }
  
  void setLMStateWrap(LMStatePtr newLMStateWrap) {
    lmstate_wrap = newLMStateWrap;
  }
  
private:
  LMStatePtr lmstate_wrap;
};

class TrieWrapper {
public:
  TrieWrapper(
    int maxChildren, 
    int rootIdx
  ): trie_wrap(std::make_shared<Trie>(maxChildren, rootIdx)) {};
  TrieWrapper(TriePtr newTrieWrap) {
    trie_wrap = newTrieWrap;
  };
  
  TriePtr& getTrieWrap() {
    return trie_wrap;
  }
  
  void setTrieWrap(TriePtr newTrieWrap) {
    trie_wrap = newTrieWrap;
  }
  
private:
  TriePtr trie_wrap;
};

class TrieNodeWrapper {
public:
  TrieNodeWrapper(
    int idx
  ): trienode_wrap(std::make_shared<TrieNode>(idx)) {};
  TrieNodeWrapper(TrieNodePtr newTrieNodeWrap) {
    trienode_wrap = newTrieNodeWrap;
  };
  
  TrieNodePtr& getTrieNodeWrap() {
    return trienode_wrap;
  }
  
  void setTrieNodeWrap(TrieNodePtr newTrieNodeWrap) {
    trienode_wrap = newTrieNodeWrap;
  }
  
private:
  TrieNodePtr trienode_wrap;
};

// class LMWrapper {
// public:
//   LMWrapper(): lm_wrap(std::make_shared<LM>()) {};
//   LMWrapper(LMPtr newLMWrap) {
//     lm_wrap = newLMWrap;
//   };
//   
//   LMPtr& getLMWrap() {
//     return lm_wrap;
//   }
//   
//   void setLMWrap(LMPtr newLMWrap) {
//     lm_wrap = newLMWrap;
//   }
//   
// private:
//   LMPtr lm_wrap;
// };


