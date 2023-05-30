#' Pipe operator
#'
#' See \code{magrittr::\link[magrittr:pipe]{\%>\%}} for details.
#'
#' @name %>%
#' @rdname pipe
#' @keywords internal
#' @export
#' @importFrom magrittr %>%
#' @usage lhs \%>\% rhs
NULL

#' Multiple assignment operator
#'
#' See \code{zeallot::\link[zeallot:operator]{\%<-\%}} for details.
#'
#' @name %<-%
#' @rdname zeallot-multi-assignment
#' @keywords internal
#' @export
#' @importFrom zeallot %<-%
#' @usage x \%<-\% value
NULL

#' Format and interpolate a string
#' 
#' See \code{glue::glue} for details.
#' 
#' @examples
#' f("iris dataset has {nrow(iris)} rows and {ncol(iris)} columns.")
#' @inheritParams glue::glue
#' @export
f <- glue::glue
