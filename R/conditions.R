type_error <- function(msg) {
  rlang::abort(msg, class = "type_error")
}

value_error <- function(msg) {
  rlang::abort(msg, class = "value_error")
}

value_warning <- function(msg) {
  rlang::warn(msg, class = "value_warning")
}

runtime_error <- function(msg) {
  rlang::abort(msg, class = "runtime_error")
}

not_implemented_error <- function(msg) {
  rlang::abort(msg, class = "not_implemented_error")
}

package_required_error <- function(pkg) {
  runtime_error(glue::glue("Package {pkg} required but not found. Please run install.packages('{pkg}') to install it."))
}

package_required <- function(pkg) {
  if(!requireNamespace(pkg, quietly = TRUE))
    package_required_error(pkg)
}
