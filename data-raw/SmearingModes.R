## code to prepare `SmearingModes` dataset goes here

SmearingModes <- list(
  NONE = "NONE",
  MAX = "MAX",
  LOGADD = "LOGADD"
)

usethis::use_data(SmearingModes, overwrite = TRUE)
