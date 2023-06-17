
#include <zlib.h>
#include <bzlib.h>
#include <lzma.h>

#include <flashlight/lib/text/dictionary/Utils.h>
#include <flashlight/lib/text/dictionary/Dictionary.h>
#include <flashlight/lib/text/decoder/lm/LM.h>
#include <flashlight/lib/text/decoder/lm/KenLM.h>
#include <flashlight/lib/text/decoder/lm/ZeroLM.h>
#include <flashlight/lib/text/decoder/Trie.h>
#include <flashlight/lib/text/decoder/LexiconDecoder.h>
#include <flashlight/lib/text/decoder/LexiconFreeDecoder.h>
#include <flashlight/lib/text/decoder/LexiconSeq2SeqDecoder.h>
#include <flashlight/lib/text/decoder/LexiconFreeSeq2SeqDecoder.h>
#include "wrappers.h"

using namespace fl::lib::text;
