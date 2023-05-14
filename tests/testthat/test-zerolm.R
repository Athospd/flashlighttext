test_that("zerolm", {
  lm <- ZeroLM$new()
  lm_state <- lm$start(FALSE)
  c(lm_state, lm_score) %<-% lm$score(lm_state, 0) 
  
  expect_s3_class(lm, "ZeroLM")
  expect_equal(lm_score, 0)
})
