## code to prepare `SmearingModes` dataset goes here

SmearingModes <- list(
  NONE = 0,
  MAX = 1,
  LOGADD = 2
)

usethis::use_data(SmearingModes, overwrite = TRUE)
