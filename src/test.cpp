
#include <stdlib.h>
#include <fstream>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include <flashlight/lib/text/decoder/LexiconDecoder.h>
#include <flashlight/lib/text/decoder/Trie.h>
#include <flashlight/lib/text/decoder/lm/KenLM.h>
#include <flashlight/lib/text/dictionary/Defines.h>
#include <flashlight/lib/text/dictionary/Dictionary.h>
#include <flashlight/lib/text/dictionary/Utils.h>
#include <flashlight/lib/text/test/Filesystem.h>

using namespace fl::lib;
using namespace fl::lib::text;

// The token dictionary for this test defines this separator token
constexpr const char* kSepToken = "|";

struct Emissions {
  std::vector<float> emission; // A column-major tensor with shape T x N.
  int nFrames{0};
  int nTokens{0};
};

/* ===================== Create Dataset ===================== */
Emissions emissionUnit;

// [[Rcpp::export]]
int test() {
  
  // T, N
  fs::path tnPath = "TN.bin";
  std::ifstream tnStream(tnPath, std::ios::binary | std::ios::in);  
  std::vector<int> tnArray(2);
  tnStream.read((char*)tnArray.data(), 2 * sizeof(int));
  int T = tnArray[0], N = tnArray[1];
  emissionUnit.nFrames = T;
  emissionUnit.nTokens = N;
  tnStream.close();
  
  emissionUnit.emission.resize(T * N);
  fs::path emissionPath = "emission.bin";
  std::ifstream em_stream(emissionPath, std::ios::binary | std::ios::in);
  em_stream.read((char*)emissionUnit.emission.data(), T * N * sizeof(float));
  em_stream.close();
  
  std::cout << T << " " << N << std::endl;
  std::cout << (T+N) << std::endl;
  std::cout << emissionUnit.emission.data() << std::endl;
  
  return N ;
};

