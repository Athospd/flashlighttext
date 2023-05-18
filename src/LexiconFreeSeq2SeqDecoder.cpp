#include <stdexcept>
#include <Rcpp.h>
#include <string>
#include <fstream>
#include <iostream>
using namespace Rcpp;
#include <flashlight/lib/text/decoder/LexiconFreeSeq2SeqDecoder.h>
#include <flashlight/lib/text/dictionary/Utils.h>
#include <flashlight/lib/text/dictionary/Dictionary.h>
#include <flashlight/lib/text/decoder/lm/LM.h>
#include <flashlight/lib/text/decoder/lm/KenLM.h>
#include <flashlight/lib/text/decoder/Trie.h>
#include "wrappers.h"
using namespace fl::lib::text;

// LexiconFreeSeq2SeqDecoderOptions //////////////////////////////////////////////////////
// constructors ------------------------------
// [[Rcpp::export]]
XPtr<LexiconFreeSeq2SeqDecoderOptions> cpp_LexiconFreeSeq2SeqDecoderOptions_constructor(
    int& beamSize, // Maximum number of hypothesis we hold after each step
    int& beamSizeToken, // Maximum number of tokens we consider at each step
    double& beamThreshold, // Threshold to prune hypothesis
    double& lmWeight, // Weight of lm
    double& eosScore, // Silence insertion score
    bool& logAdd // If or not use logadd when merging hypothesis
) {
  LexiconFreeSeq2SeqDecoderOptions* obj = new LexiconFreeSeq2SeqDecoderOptions;
  *obj = {
    beamSize,
    beamSizeToken,
    beamThreshold,
    lmWeight,
    eosScore,
    logAdd
  };
  XPtr<LexiconFreeSeq2SeqDecoderOptions> ptr(obj, true);
  return ptr;
}

// methods ------------------------------
// [[Rcpp::export]]
void cpp_LexiconFreeSeq2SeqDecoderOptions_set_beamSize(XPtr<LexiconFreeSeq2SeqDecoderOptions> obj, int value) {obj->beamSize = value;}
// [[Rcpp::export]]
int cpp_LexiconFreeSeq2SeqDecoderOptions_get_beamSize(XPtr<LexiconFreeSeq2SeqDecoderOptions> obj) {return obj->beamSize;}
// [[Rcpp::export]]
void cpp_LexiconFreeSeq2SeqDecoderOptions_set_beamSizeToken(XPtr<LexiconFreeSeq2SeqDecoderOptions> obj, int value) {obj->beamSizeToken = value;}
// [[Rcpp::export]]
int cpp_LexiconFreeSeq2SeqDecoderOptions_get_beamSizeToken(XPtr<LexiconFreeSeq2SeqDecoderOptions> obj) {return obj->beamSizeToken;}
// [[Rcpp::export]]
void cpp_LexiconFreeSeq2SeqDecoderOptions_set_beamThreshold(XPtr<LexiconFreeSeq2SeqDecoderOptions> obj, double value) {obj->beamThreshold = value;}
// [[Rcpp::export]]
double cpp_LexiconFreeSeq2SeqDecoderOptions_get_beamThreshold(XPtr<LexiconFreeSeq2SeqDecoderOptions> obj) {return obj->beamThreshold;}
// [[Rcpp::export]]
void cpp_LexiconFreeSeq2SeqDecoderOptions_set_lmWeight(XPtr<LexiconFreeSeq2SeqDecoderOptions> obj, double value) {obj->lmWeight = value;}
// [[Rcpp::export]]
double cpp_LexiconFreeSeq2SeqDecoderOptions_get_lmWeight(XPtr<LexiconFreeSeq2SeqDecoderOptions> obj) {return obj->lmWeight;}
// [[Rcpp::export]]
void cpp_LexiconFreeSeq2SeqDecoderOptions_set_eosScore(XPtr<LexiconFreeSeq2SeqDecoderOptions> obj, double value) {obj->eosScore = value;}
// [[Rcpp::export]]
double cpp_LexiconFreeSeq2SeqDecoderOptions_get_eosScore(XPtr<LexiconFreeSeq2SeqDecoderOptions> obj) {return obj->eosScore;}
// [[Rcpp::export]]
void cpp_LexiconFreeSeq2SeqDecoderOptions_set_logAdd(XPtr<LexiconFreeSeq2SeqDecoderOptions> obj, bool value) {obj->logAdd = value;}
// [[Rcpp::export]]
bool cpp_LexiconFreeSeq2SeqDecoderOptions_get_logAdd(XPtr<LexiconFreeSeq2SeqDecoderOptions> obj) {return obj->logAdd;}


// LexiconFreeSeq2SeqDecoder /////////////////////////////////////////////////////////
// constructors ------------------------------
// [[Rcpp::export]]  
XPtr<LexiconFreeSeq2SeqDecoder> cpp_LexiconFreeSeq2SeqDecoder_constructor(
    XPtr<LexiconFreeSeq2SeqDecoderOptions> opt,
    XPtr<LMWrapper> lm,
    int eos,
    XPtr<EmittingModelUpdateFunc> emitting_model_update_func,
    int max_output_length
) {
  LexiconFreeSeq2SeqDecoderOptions opt_ = *opt;
  EmittingModelUpdateFunc emitting_model_update_func_ = *emitting_model_update_func;
  LexiconFreeSeq2SeqDecoder *decoder = new LexiconFreeSeq2SeqDecoder(
    opt_,
    lm->getLMWrap(), 
    eos, 
    emitting_model_update_func_,
    max_output_length
  );
  
  XPtr<LexiconFreeSeq2SeqDecoder> ptr(decoder, true);
  return ptr;
}

