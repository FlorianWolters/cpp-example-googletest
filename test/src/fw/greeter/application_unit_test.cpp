/// @file
/// Defines unit tests for the the `fw::greeter::Application` concrete class.
///
/// @author Florian Wolters <wolters.fl@gmail.com>
/// @copyright Copyright (c) 2019, Florian Wolters and/or its affiliates.
/// All rights reserved.
/// This code is licensed under the MIT License. See `LICENSE` file for details.

// Google Test
#include <gmock/gmock.h>

#include <fw/greeter/application.hpp>

#include <fw/greeter/testing/command_line_mock.hpp>
#include <fw/greeter/testing/config_mock.hpp>
#include <fw/greeter/testing/personal_name_repository_mock.hpp>

namespace {

using fw::greeter::Application;
using fw::greeter::testing::CommandLineMock;
using fw::greeter::testing::ConfigMock;
using fw::greeter::testing::PersonalNameRepositoryMock;

TEST(
    ApplicationUnitTest,
    GivenPersonalNameRepositoryReturnsThreeEntriesWhenRunThenThreeNamesAreWrittenToOutputStream) {
  // Arrange
  auto const findAllResult = std::vector<fw::greeter::PersonalName>{
      fw::greeter::PersonalName{"Wolfgang Amadeus Mozart"},
      fw::greeter::PersonalName{"Kurt Donald Cobain"},
      fw::greeter::PersonalName{"James Hetfield"}};

  // Create test doubles
  auto personalNameRepository = PersonalNameRepositoryMock{};
  auto config = ConfigMock{};
  auto cli = CommandLineMock{};
  auto standardOutput = std::ostringstream{};
  auto standardError = std::ostringstream{};

  using ::testing::AnyNumber;
  using ::testing::Return;
  using ::testing::ReturnRef;

  // Assert (part 1)

  // Setup expectations for the `PersonalNameRepositoryMock`.
  EXPECT_CALL(personalNameRepository, findAll())
      .Times(AnyNumber())
      .WillRepeatedly(Return(findAllResult));

  // Setup expectations for the `ConfigMock`.
  EXPECT_CALL(config, personalNameRepository())
      .Times(AnyNumber())
      .WillRepeatedly(ReturnRef(personalNameRepository));

  // Setup expectations for the `CommandLineMock`.
  EXPECT_CALL(cli, parse()).Times(AnyNumber());
  EXPECT_CALL(cli, config())
      .Times(AnyNumber())
      .WillRepeatedly(ReturnRef(config));
  EXPECT_CALL(cli, standardOutput())
      .Times(AnyNumber())
      .WillRepeatedly(ReturnRef(standardOutput));
  EXPECT_CALL(cli, standardError())
      .Times(AnyNumber())
      .WillRepeatedly(ReturnRef(standardError));

  // Create the System Under Test (SUT).
  auto const sut = Application{cli};
  auto const expected = R"(Wolfgang Amadeus Mozart
Kurt Donald Cobain
James Hetfield
)";
  // Act
  auto const exitCode = sut.run();

  // Assert (part 2)
  ASSERT_EQ(0, exitCode);
  ASSERT_TRUE(standardError.str().empty());
  ASSERT_EQ(expected, standardOutput.str());
}

ACTION(ThrowUnknownException) {
  throw 0;
}

TEST(
    ApplicationUnitTest,
    GivenCommandLineInterfaceThrowsUnknownExceptionThenMessageIsWrittenToErrorStream) {
  // Arrange
  auto cli = CommandLineMock{};
  auto standardError = std::ostringstream{};

  using ::testing::AnyNumber;
  using ::testing::ReturnRef;

  // Assert (part 1)
  // Setup expectations for the `CommandLineMock`.
  EXPECT_CALL(cli, parse())
      .Times(AnyNumber())
      .WillRepeatedly(ThrowUnknownException());
  EXPECT_CALL(cli, standardError())
      .Times(AnyNumber())
      .WillRepeatedly(ReturnRef(standardError));

  auto const sut = Application{cli};

  // Act
  auto const exitCode = sut.run();

  // Assert
  ASSERT_EQ("Unknown exception in fw::greeter::Application\n",
            standardError.str());
}

}  // namespace
