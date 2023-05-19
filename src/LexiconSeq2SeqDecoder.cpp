#include <stdexcept>
#include <Rcpp.h>
#include <string>
#include <fstream>
#include <iostream>
using namespace Rcpp;
// [[Rcpp::plugins(cpp17)]]
#include <flashlight/lib/text/decoder/LexiconSeq2SeqDecoder.h>
#include <flashlight/lib/text/dictionary/Utils.h>
#include <flashlight/lib/text/dictionary/Dictionary.h>
#include <flashlight/lib/text/decoder/lm/KenLM.h>
#include <flashlight/lib/text/decoder/Trie.h>
#include "wrappers.h"
using namespace fl::lib::text;

// LexiconSeq2SeqDecoderOptions //////////////////////////////////////////////////////
// constructors ------------------------------
// [[Rcpp::export]]
XPtr<LexiconSeq2SeqDecoderOptions> cpp_LexiconSeq2SeqDecoderOptions_constructor(
    int& beamSize, // Maximum number of hypothesis we hold after each step
    int& beamSizeToken, // Maximum number of tokens we consider at each step
    double& beamThreshold, // Threshold to prune hypothesis
    double& lmWeight, // Weight of lm
    double& wordScore, // Word insertion score
    double& eosScore, // Score for inserting an EOS
    bool& logAdd // If or not use logadd when merging hypothesis
) {
  LexiconSeq2SeqDecoderOptions* obj = new LexiconSeq2SeqDecoderOptions;
  *obj = {
    beamSize,
    beamSizeToken,
    beamThreshold,
    lmWeight,
    wordScore,
    eosScore,
    logAdd
  };
  XPtr<LexiconSeq2SeqDecoderOptions> ptr(obj, true);
  return ptr;
}

// methods ------------------------------
// [[Rcpp::export]]
void cpp_LexiconSeq2SeqDecoderOptions_set_beamSize(XPtr<LexiconSeq2SeqDecoderOptions> obj, int value) {obj->beamSize = value;}
// [[Rcpp::export]]
int cpp_LexiconSeq2SeqDecoderOptions_get_beamSize(XPtr<LexiconSeq2SeqDecoderOptions> obj) {return obj->beamSize;}
// [[Rcpp::export]]
void cpp_LexiconSeq2SeqDecoderOptions_set_beamSizeToken(XPtr<LexiconSeq2SeqDecoderOptions> obj, int value) {obj->beamSizeToken = value;}
// [[Rcpp::export]]
int cpp_LexiconSeq2SeqDecoderOptions_get_beamSizeToken(XPtr<LexiconSeq2SeqDecoderOptions> obj) {return obj->beamSizeToken;}
// [[Rcpp::export]]
void cpp_LexiconSeq2SeqDecoderOptions_set_beamThreshold(XPtr<LexiconSeq2SeqDecoderOptions> obj, double value) {obj->beamThreshold = value;}
// [[Rcpp::export]]
double cpp_LexiconSeq2SeqDecoderOptions_get_beamThreshold(XPtr<LexiconSeq2SeqDecoderOptions> obj) {return obj->beamThreshold;}
// [[Rcpp::export]]
void cpp_LexiconSeq2SeqDecoderOptions_set_lmWeight(XPtr<LexiconSeq2SeqDecoderOptions> obj, double value) {obj->lmWeight = value;}
// [[Rcpp::export]]
double cpp_LexiconSeq2SeqDecoderOptions_get_lmWeight(XPtr<LexiconSeq2SeqDecoderOptions> obj) {return obj->lmWeight;}
// [[Rcpp::export]]
void cpp_LexiconSeq2SeqDecoderOptions_set_wordScore(XPtr<LexiconSeq2SeqDecoderOptions> obj, double value) {obj->wordScore = value;}
// [[Rcpp::export]]
double cpp_LexiconSeq2SeqDecoderOptions_get_wordScore(XPtr<LexiconSeq2SeqDecoderOptions> obj) {return obj->wordScore;}
// [[Rcpp::export]]
void cpp_LexiconSeq2SeqDecoderOptions_set_eosScore(XPtr<LexiconSeq2SeqDecoderOptions> obj, double value) {obj->eosScore = value;}
// [[Rcpp::export]]
double cpp_LexiconSeq2SeqDecoderOptions_get_eosScore(XPtr<LexiconSeq2SeqDecoderOptions> obj) {return obj->eosScore;}
// [[Rcpp::export]]
void cpp_LexiconSeq2SeqDecoderOptions_set_logAdd(XPtr<LexiconSeq2SeqDecoderOptions> obj, bool value) {obj->logAdd = value;}
// [[Rcpp::export]]
bool cpp_LexiconSeq2SeqDecoderOptions_get_logAdd(XPtr<LexiconSeq2SeqDecoderOptions> obj) {return obj->logAdd;}



// LexiconSeq2SeqDecoder /////////////////////////////////////////////////////////
// constructors ------------------------------
// [[Rcpp::export]]  
XPtr<LexiconSeq2SeqDecoder> cpp_LexiconSeq2SeqDecoder_constructor(
    XPtr<LexiconSeq2SeqDecoderOptions> opt,
    XPtr<TrieWrapper> lexicon,
    XPtr<LMWrapper> lm,
    int eos,
    XPtr<EmittingModelUpdateFunc> emitting_model_update_func,
    int max_output_length,
    bool is_lm_token
) {
  LexiconSeq2SeqDecoderOptions opt_ = *opt;
  EmittingModelUpdateFunc emitting_model_update_func_ = *emitting_model_update_func;
  // EmittingModelUpdateFunc* emitting_model_update_func_ = new EmittingModelUpdateFunc();
  LexiconSeq2SeqDecoder *decoder = new LexiconSeq2SeqDecoder(
    opt_,
    lexicon->getTrieWrap(), 
    lm->getLMWrap(), 
    eos, 
    emitting_model_update_func_, 
    max_output_length, 
    is_lm_token
  );
  
  XPtr<LexiconSeq2SeqDecoder> ptr(decoder, true);
  return ptr;
}

