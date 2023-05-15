test_that("LM", {
  expect_no_error(lm <- LM$new())
  expect_null(lm$ptr)
  expect_error(state <- lm$start(FALSE), regexp = "start")
  expect_error(state <- lm$score(), regexp = "score")
  expect_error(lm$finish(), regexp = "finish")
})
