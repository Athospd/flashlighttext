test_that("Dictionary", {
  dict <- Dictionary$new()
  dict$add_entry("1", 1)
  dict$add_entry("2", 2)
  dict$add_entry("3", 3)
  dict$add_entry("4", 3)
  
  expect_equal(dict$get_entry(1), "1")
  expect_equal(dict$get_entry(3), "3")
  
  expect_equal(dict$get_index("2"), 2)
  expect_equal(dict$get_index("4"), 3)
  
  expect_equal(dict$entry_size(), 4)
  expect_equal(dict$index_size(), 3)
  
  dict$add_entry("5")
  expect_equal(dict$get_index("5"), 4)
  expect_equal(dict$entry_size(), 5)
  
  dict$add_entry("6")
  expect_equal(dict$get_index("6"), 5)
  expect_equal(dict$index_size(), 5)
  
  expect_equal(dict$get_entry(1), "1")
  expect_equal(dict$get_entry(3), "3")
  
  expect_equal(dict$get_index("2"), 2)
  expect_equal(dict$get_index("4"), 3)
  
  expect_equal(dict$entry_size(), 6)
  expect_equal(dict$index_size(), 5)
  
  
  expect_equal(dict$get_index(c("5", "6")), c(4, 5))
  expect_equal(dict$get_index(c("6", "5")), c(5, 4))
})

test_that("Dictionary from file", {
  expect_error(Dictionary$new("not_a_real_file"))
  dict <- Dictionary$new(
    system.file("test.dict", package = "flashlighttext")
  )
  expect_equal(dict$entry_size(), 10)
  expect_equal(dict$index_size(), 7)
  expect_true(dict$contains("a"))
  expect_false(dict$contains("q"))
  expect_equal(dict$get_entry(1), "b")
  expect_equal(dict$get_index("e"), 4)
})

test_that("Dictionary packReplabels", {
  dict <- Dictionary$new()
  dict$add_entry("<1>", 1)
  dict$add_entry("<2>", 2)
  dict$add_entry("<3>", 3)
  
  labels = c(5, 6, 6, 6, 10, 8, 8, 10, 10, 10, 10, 10)
  packedCheck = list()
  packedCheck[[1]] = c(5, 6, 6, 6, 10, 8, 8, 10, 10, 10, 10, 10)
  packedCheck[[2]] = c(5, 6, 1, 6, 10, 8, 1, 10, 1, 10, 1, 10)
  packedCheck[[3]] = c(5, 6, 2, 10, 8, 1, 10, 2, 10, 1)
  packedCheck[[4]] = c(5, 6, 2, 10, 8, 1, 10, 3, 10)
  
  for (i in seq.int(nrow(packedCheck))) {
    packed = pack_replabels(labels, dict, i - 1)
    expect_equal(packed, packedCheck[[i]])
    unpacked = unpack_replabels(packed, dict, i - 1)
    expect_equal(unpacked, labels)
  }
  
  dict <- Dictionary$new()
  dict$add_entry("<1>", 1)
  dict$add_entry("<2>", 2)
  dict$add_entry("<3>", 3)
  dict$add_entry("1", 4)
  dict$add_entry("2", 5)
  dict$add_entry("3", 6)
  labels = c(6, 3, 7, 2, 8, 0, 1)
  
  unpacked1 = unpack_replabels(labels, dict, 1)
  expect_equal(unpacked1, c(6, 3, 7, 2, 8, 0, 0))
  
  unpacked2 = unpack_replabels(labels, dict, 2)
  expect_equal(unpacked2, c(6, 3, 7, 7, 7, 8, 0, 0))
  
  unpacked3 = unpack_replabels(labels, dict, 3)
  expect_equal(unpacked3, c(6, 6, 6, 6, 7, 7, 7, 8, 0, 0))
  
  dict = Dictionary$new()
  dict$add_entry("<1>", 1)
  dict$add_entry("<2>", 2)
  dict$add_entry("1", 3)
  dict$add_entry("2", 4)
  
  # The initial replabel "<1>", with no prior token to repeat, is ignored.
  labels1 = c(1, 5, 1, 6)
  unpacked1 = unpack_replabels(labels1, dict, 2)
  expect_equal(unpacked1, c(5, 5, 6))
  
  # The final replabel "<2>", whose prior token is a replabel, is ignored.
  labels2 = c(1, 5, 1, 2, 6)
  unpacked2 = unpack_replabels(labels2, dict, 2)
  expect_equal(unpacked2, c(5, 5, 6))
  
  # With maxReps=1, "<2>" is not considered a replabel, altering the result.
  unpacked2_1 = unpack_replabels(labels2, dict, 1)
  expect_equal(unpacked2_1, c(5, 5, 2, 6))
  
  # All replabels past the first "1" are ignored here.
  labels3 = c(5, 1, 2, 1, 2, 6)
  unpacked3 = unpack_replabels(labels3, dict, 2)
  expect_equal(unpacked3, c(5, 5, 6))
  
})
