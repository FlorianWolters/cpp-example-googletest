/// @file
/// Demonstrates the usage of *Google Test* assertions.
///
/// @author Florian Wolters <wolters.fl@gmail.com>
/// @copyright Copyright (c) 2019, Florian Wolters and/or its affiliates.
/// All rights reserved.
/// This code is licensed under the MIT License. See `LICENSE` file for details.

// Google Test
#include <gtest/gtest.h>

// Standard Library
#include <stdexcept>

namespace {

// Simple Tests
TEST(TestCaseClassName, TestMethodName) {
  // Test Method implementation
}

// https://github.com/google/googletest/blob/master/googletest/docs/primer.md#assertions

// https://github.com/google/googletest/blob/master/googletest/docs/primer.md#basic-assertions
TEST(AssertionsTest, BasicAssertions) {
  ASSERT_TRUE(true);
  ASSERT_FALSE(false);
}

// https://github.com/google/googletest/blob/master/googletest/docs/primer.md#binary-comparison
TEST(AssertionsTest, BinaryComparison) {
  ASSERT_EQ(0, 0);
  ASSERT_NE(0, 1);
  ASSERT_LT(0, 1);
  ASSERT_LE(0, 0);
  ASSERT_GT(1, 0);
  ASSERT_GE(0, 0);
}

// https://github.com/google/googletest/blob/master/googletest/docs/primer.md#simple-tests
TEST(AssertionsTest, StringComparison) {
  ASSERT_STREQ("foo", "foo");
  ASSERT_STRNE("foo", "FOO");
  ASSERT_STRCASEEQ("foo", "FOO");
  ASSERT_STRCASENE("foo", "bar");
}

// More assertions

// https://github.com/google/googletest/blob/master/googletest/docs/advanced.md#explicit-success-and-failure
TEST(AssertionsTest, ExplicitSuccess) {
  SUCCEED() << "Explicit success without assertion";
}

TEST(AssertionsTest, ExplicitFailure) {
  FAIL() << "Explicit failure without assertion";
}

// https://github.com/google/googletest/blob/master/googletest/docs/advanced.md#exception-assertions
TEST(AssertionsTest, Exceptions) {
  ASSERT_THROW(throw std::runtime_error{""}, std::runtime_error);
  ASSERT_ANY_THROW(throw std::runtime_error{""});
  ASSERT_NO_THROW(true);
}

TEST(StringTest, EmptyOnDefaultConstructedInstanceReturnsTrue) {
  // Arrange
  auto const sut = std::string{};
  // Act
  auto const result = sut.empty();
  // Assert
  ASSERT_TRUE(result);
}

TEST(StringTest,
     GivenDefaultConstructedInstanceWhenEmptyIsCalledThenTrueIsReturned) {
  // Arrange
  auto const sut = std::string{};
  // Act
  auto const result = sut.empty();
  // Assert
  ASSERT_TRUE(result);
}

}  // namespace
