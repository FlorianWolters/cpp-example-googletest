/// @file
/// Defines tests for the the `fw::greeter::PersonalName` concrete class.
///
/// @author Florian Wolters <wolters.fl@gmail.com>
/// @copyright Copyright (c) 2019, Florian Wolters and/or its affiliates.
/// All rights reserved.
/// This code is licensed under the MIT License. See `LICENSE` file for details.

// Google Test
#include <gtest/gtest.h>

#include <fw/greeter/personal_name.hpp>

namespace {

using fw::InvalidArgument;
using fw::greeter::PersonalName;

class PersonalNameWithFirstAndMiddleAndLastTest : public ::testing::Test {
 protected:
  PersonalName sut_{"Kurt", "Donald", "Cobain"};
};

TEST_F(PersonalNameWithFirstAndMiddleAndLastTest,
       FirstAfterConstructionReturns1stConstructorArg) {
  ASSERT_EQ("Kurt", sut_.first());
}

TEST_F(PersonalNameWithFirstAndMiddleAndLastTest,
       MiddleAfterConstructionReturns2ndConstructorArg) {
  ASSERT_EQ("Donald", sut_.middle());
}

TEST_F(PersonalNameWithFirstAndMiddleAndLastTest,
       LastAfterConstructionReturns3rdConstructorArg) {
  ASSERT_EQ("Cobain", sut_.last());
}

TEST_F(
    PersonalNameWithFirstAndMiddleAndLastTest,
    FullAfterConstructionReturnsFirstAndSecondAndThirdSeparatedByOneSpaceCharacter) {
  ASSERT_EQ("Kurt Donald Cobain", sut_.full());
}

TEST(PersonalNameTest,
     FullAfterConstructionWithEmptyMiddleNameReturnsExpected) {
  auto const sut = PersonalName{"Kurt", "", "Cobain"};
  ASSERT_EQ("Kurt Cobain", sut.full());
}

TEST(PersonalNameTest,
     GivenEmptyFirstNameWhenConstructedThenThrowsInvalidArgument) {
  // Note that the Google Test assertion macros do not support C++11 "Uniform
  // Initialization".
  ASSERT_THROW(PersonalName("", "Donald", "Cobain"), InvalidArgument);
}

TEST(PersonalNameTest,
     GivenEmptyLastNameWhenConstructedThenThrowsInvalidArgument) {
  ASSERT_THROW(PersonalName("Kurt", "Donald", ""), InvalidArgument);
}

TEST(PersonalNameTest, GivenEmptyMiddleNameWhenConstructedThenDoesNotThrow) {
  ASSERT_NO_THROW(PersonalName("Kurt", "", "Cobain"));
}

TEST(PersonalNameTest, GivenOnePartOneArgConstructorThrowsInvalidArgument) {
  ASSERT_THROW(PersonalName("Max"), InvalidArgument);
}

TEST(PersonalNameTest, GivenTwoPartsOneArgConstructorReturnsExpected) {
  auto const sut = PersonalName{"Kurt Cobain"};
  ASSERT_EQ("Kurt", sut.first());
  ASSERT_EQ("", sut.middle());
  ASSERT_EQ("Cobain", sut.last());
  ASSERT_EQ("Kurt Cobain", sut.full());
}

TEST(PersonalNameTest, GivenThreePartsOneArgConstructorReturnsExpected) {
  auto const sut = PersonalName{"Wolfgang Amadeus Mozart"};
  ASSERT_EQ("Wolfgang", sut.first());
  ASSERT_EQ("Amadeus", sut.middle());
  ASSERT_EQ("Mozart", sut.last());
  ASSERT_EQ("Wolfgang Amadeus Mozart", sut.full());
}

}  // namespace
