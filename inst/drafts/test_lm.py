import math
import os
import pickle
import struct
import sys
import unittest
from dataclasses import dataclass

import numpy as np
from flashlight.lib.text.decoder import (
    CriterionType as _CriterionType,
    LexiconDecoder as _LexiconDecoder,
    LexiconDecoderOptions as _LexiconDecoderOptions,
    LexiconFreeDecoder as _LexiconFreeDecoder,
    LexiconFreeDecoderOptions as _LexiconFreeDecoderOptions,
    LM as _LM,
    LMState as _LMState,
    SmearingMode as _SmearingMode,
    Trie as _Trie,
    ZeroLM as _ZeroLM,
)
from flashlight.lib.text.dictionary import (
    create_word_dict,
    Dictionary,
    load_words,
    pack_replabels,
)


lm = _LM()


state = lm.start(False)
state = lm.score()
lm.finish()
