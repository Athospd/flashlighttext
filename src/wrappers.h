
#include <flashlight/lib/text/decoder/lm/KenLM.h>
#include <flashlight/lib/text/decoder/Trie.h>
using namespace fl::lib::text;

using KenLMPtr = std::shared_ptr<KenLM>;
using TriePtr = std::shared_ptr<Trie>;

class KenLMWrapper {
public:
  KenLMPtr kenlm_wrap;
  KenLMWrapper(
    const std::string& path, 
    const Dictionary& usrTknDict
  ): kenlm_wrap(std::make_shared<KenLM>(path, usrTknDict)) {};
};

class TrieWrapper {
public:
  TriePtr trie_wrap;
  TrieWrapper(
    int maxChildren, 
    int rootIdx
  ): trie_wrap(std::make_shared<Trie>(maxChildren, rootIdx)) {};
};
