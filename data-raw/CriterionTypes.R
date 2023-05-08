## code to prepare `CriterionTypes` dataset goes here

CriterionTypes <- list(
  ASG = "ASG",
  CTC = "CTC",
  S2S = "S2S"
)

usethis::use_data(CriterionTypes, overwrite = TRUE)
