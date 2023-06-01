#' @useDynLib flashlighttext
#' @importFrom Rcpp sourceCpp
NULL


#' @import R6
NULL

is_null_externalptr <- function(x) {
  identical(x, methods::new("externalptr"))
}

globalVariables(c("SmearingModes"))
