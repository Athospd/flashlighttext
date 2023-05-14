import math
import os
import pickle
import struct
import sys
import unittest
from dataclasses import dataclass

import numpy as np
from flashlight.lib.text.decoder import (
    create_emitting_model_state,
    CriterionType,
    get_obj_from_emitting_model_state,
    LexiconDecoder,
    LexiconDecoderOptions,
    LexiconFreeDecoder,
    LexiconFreeDecoderOptions,
    LexiconFreeSeq2SeqDecoder,
    LexiconFreeSeq2SeqDecoderOptions,
    SmearingMode,
    Trie,
    ZeroLM,
)
from flashlight.lib.text.dictionary import (
    create_word_dict,
    Dictionary,
    load_words,
    pack_replabels,
)


def read_struct(file, fmt):
    return struct.unpack(fmt, file.read(struct.calcsize(fmt)))


def load_tn(path):
    """
    Load time size and number of tokens from the dump
    (defines the score to move from token_i to token_j)

    Returns:
    --------
    int, int
    """
    with open(path, "rb") as file:
        T = read_struct(file, "i")[0]
        N = read_struct(file, "i")[0]
        return T, N


def load_emissions(path, T, N):
    """
    Load precomputed transition matrix
    (defines the score to move from token_i to token_j)

    Returns:
    --------
    numpy.array of shape [Batch=1, Time, Ntokens]
    """
    with open(path, "rb") as file:
        return np.frombuffer(file.read(T * N * 4), dtype=np.float32)


def load_transitions(path, N):
    """
    Load precomputed transition matrix
    (defines the score to move from token_i to token_j)

    Returns:
    --------
    numpy.array of shape [Ntokens, Ntokens]
    """
    with open(path, "rb") as file:
        return np.frombuffer(file.read(N * N * 4), dtype=np.float32)


def tkn_to_idx(spelling, token_dict, maxReps=0):
    result = []
    for token in spelling:
        result.append(token_dict.get_index(token))
    return pack_replabels(result, token_dict, maxReps)

from flashlight.lib.text.decoder.kenlm import KenLM

data_path = "inst/"

T, N = load_tn(os.path.join(data_path, "TN.bin"))

emissions = load_emissions(os.path.join(data_path, "emission.bin"), T, N)
# load transitions (from ASG loss optimization) [Ntokens, Ntokens]
transitions = load_transitions(os.path.join(data_path, "transition.bin"), N)
# load lexicon file, which defines spelling of words
# the format word and its tokens spelling separated by the spaces,
# for example for letters tokens with ASG loss:
# ann a n 1 |
lexicon = load_words(os.path.join(data_path, "words.lst"))
# read lexicon and store it in the w2l dictionary
word_dict = create_word_dict(lexicon)
# create w2l dict with tokens set (letters in this example)
token_dict = Dictionary(os.path.join(data_path, "letters.lst"))
# add repetition symbol as soon as we have ASG emitting model
token_dict.add_entry("<1>")
# create Kenlm language model
lm = KenLM(os.path.join(data_path, "lm.arpa"), word_dict)

# test LM
sentence = ["the", "cat", "sat", "on", "the", "mat"]
# start LM with nothing, get its current state
lm_state = lm.start(False)
total_score = 0
lm_score_target = [-1.05971, -4.19448, -3.33383, -2.76726, -1.16237, -4.64589]
# iterate over words in the sentence
for i in range(len(sentence)):
    # score lm, taking current state and index of the word
    # returns new state and score for the word
    lm_state, lm_score = lm.score(lm_state, word_dict.get_index(sentence[i]))
    # add score of the current word to the total sentence score
    total_score += lm_score

# move lm to the final state, the score returned is for eos
lm_state, lm_score = lm.finish(lm_state)
total_score += lm_score

separator_idx = token_dict.get_index("|")
# get unknown word index
unk_idx = word_dict.get_index("<unk>")
# create the trie, specifying how many tokens we have and silence index
trie = Trie(token_dict.index_size(), separator_idx)
start_state = lm.start(False)
for word, spellings in lexicon.items():
    usr_idx = word_dict.get_index(word)
    _, score = lm.score(start_state, usr_idx)
    # print(word + " - " + str(usr_idx) + " - " + str(score))
    for spelling in spellings:
        # max_reps should be 1; using 0 here to match DecoderTest bug
        spelling_idxs = tkn_to_idx(spelling, token_dict, 1)
        print("   >> " + "".join([str(x) for x in spelling]) + " - " + "".join([str(x) for x in spelling_idxs]))
        # trie.insert(spelling_idxs, usr_idx, score)

trie.smear(SmearingMode.MAX)
# check that trie is built in consistency with c++
trie_score_target = [-1.05971, -2.87742, -2.64553, -3.05081, -1.05971, -3.08968]
for i in range(len(sentence)):
  word = sentence[i]
  # max_reps should be 1; using 0 here to match DecoderTest bug
  word_tensor = tkn_to_idx([c for c in word], token_dict, 1)
  node = trie.search(word_tensor)
  print(node.max_score - trie_score_target[i])


opts = LexiconDecoderOptions(
    beam_size=2500,
    beam_size_token=25000,
    beam_threshold=100.0,
    lm_weight=2.0,
    word_score=2.0,
    unk_score=-math.inf,
    sil_score=-1,
    log_add=False,
    criterion_type=CriterionType.ASG,
)

# define lexicon beam-search decoder with word-level lm
# LexiconDecoder(decoder options, trie, lm, silence index,
#                blank index (for CTC), unk index,
#                transitions matrix, is token-level lm)
decoder = LexiconDecoder(
    options=opts,
    trie=trie,
    lm=lm,
    sil_token_idx=separator_idx,
    blank_token_idx=-1,
    unk_token_idx=unk_idx,
    transitions=transitions,
    is_token_lm=False,
)

# run decoding
# decoder.decode(emissions, Time, Ntokens)
# result is a list of sorted hypothesis, 0-index is the best hypothesis
# each hypothesis is a struct with "score" and "words" representation
# in the hypothesis and the "tokens" representation
results = decoder.decode(emissions.ctypes.data, T, N)
results[0].score # -1297.238538974896
results[0].lmScore # -2.6859140396118164
results[0].emittingModelScore # -1056.8667108956724
print(f"Decoding complete, obtained {len(results)} results")
print("Showing top 5 results:")
for i in range(min(5, len(results))):
  prediction = []
  for idx in results[i].tokens:
      if idx < 0:
          break
      prediction.append(token_dict.get_entry(idx))
  prediction = " ".join(prediction)
  print(
      f"score={results[i].score} emittingModelScore={results[i].emittingModelScore} lmScore={results[i].lmScore} prediction='{prediction}'"
  )


(len(results) == 16)
hyp_score_target = [-284.0998, -284.108, -284.119, -284.127, -284.296]
for i in range(min(5, len(results))):
    (results[i].score - hyp_score_target[i])

