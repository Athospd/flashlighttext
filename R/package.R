#' @useDynLib flashlighttext
#' @importFrom Rcpp sourceCpp
NULL

is_null_externalptr <- function(x) {
  identical(x, new("externalptr"))
}


