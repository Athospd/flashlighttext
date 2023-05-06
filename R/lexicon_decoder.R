# LexiconDecoder <- R6::R6Class(
#   "LexiconDecoder",
#   inherit = Decoder,
#   public = list(
#     initialize = function(
#     opt, lexicon, lm, sil, blank, unk, transitions, isLmToken
#     ) {
#       self$opt_ <- opt
#       self$lexicon_ <- lexicon
#       self$lm_ <- lm
#       self$sil_ <- sil
#       self$blank_ <- blank
#       self$unk_ <- unk
#       self$transitions_ <- transitions
#       self$isLmToken_ <- isLmToken
#       self$candidates_ <- list()
#       self$candidatePtrs_ <- list()
#       self$candidatesBestScore_ <- 0
#       self$hyp_ <- list()
#       self$nDecodedFrames_ <- 0
#       self$nPrunedFrames_ <- 0
#     },
#     decodeBegin = function() {},
#     decodeStep = function(emissions, T, N) {},
#     decodeEnd = function() {},
#     nHypothesis = function() {},
#     prune = function(lookBack = 0) {},
#     nDecodedFramesInBuffer = function() {},
#     getBestHypothesis = function(lookBack = 0) {},
#     getAllFinalHypothesis = function() {}
#   ),
#   private = list(
#     opt_ = NULL,
#     lexicon_ = NULL,
#     lm_ = NULL,
#     sil_ = NULL,
#     blank_ = NULL,
#     unk_ = NULL,
#     transitions_ = NULL,
#     isLmToken_ = NULL,
#     candidates_ = NULL,
#     candidatePtrs_ = NULL,
#     candidatesBestScore_ = NULL,
#     hyp_ = NULL,
#     nDecodedFrames_ = NULL,
#     nPrunedFrames_ = NULL
#   )
# )
