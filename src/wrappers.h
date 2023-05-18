
#include <flashlight/lib/text/decoder/lm/LM.h>
#include <flashlight/lib/text/decoder/lm/KenLM.h>
#include <flashlight/lib/text/decoder/lm/ZeroLM.h>
#include <flashlight/lib/text/decoder/Trie.h>
using namespace fl::lib::text;

using LMPtr = std::shared_ptr<LM>;
using LMStatePtr = std::shared_ptr<LMState>;
using TriePtr = std::shared_ptr<Trie>;

class LMWrapper {
  public:
    LMPtr lm_wrap;
    
    LMPtr& getLMWrap() {
      return lm_wrap;
    }
    
    void setLMWrap(LMPtr newLMWrap) {
      lm_wrap = newLMWrap;
    }
};

class ZeroLMWrapper : public LMWrapper {
  public:
    ZeroLMWrapper() {
      this->setLMWrap(std::make_shared<ZeroLM>());
    }
};

class KenLMWrapper : public LMWrapper {
  public:
    KenLMWrapper(
      const std::string& path, 
      const Dictionary& usrTknDict
    ) {
      this->setLMWrap(std::make_shared<KenLM>(path, usrTknDict));
    }
    
    KenLMWrapper(LMPtr& newKenLMWrap) {
      this->setLMWrap(newKenLMWrap);
    }
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



