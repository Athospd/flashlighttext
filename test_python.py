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
