/// @file
/// Defines integration tests for the the `fw::greeter::Application` concrete
/// class.
///
/// @author Florian Wolters <wolters.fl@gmail.com>
/// @copyright Copyright (c) 2019, Florian Wolters and/or its affiliates.
/// All rights reserved.
/// This code is licensed under the MIT License. See `LICENSE` file for details.

// Google Test
#include <gtest/gtest.h>

// Standard Library
#include <cstring>
#include <filesystem>

#include <fw/greeter/application.hpp>
#include <fw/greeter/command_line.hpp>

namespace {

using fw::greeter::Application;

class ApplicationIntegrationTest : public ::testing::Test {
 protected:
  ApplicationIntegrationTest() {}

  auto createCli(std::filesystem::path const& inputFile)
      -> fw::greeter::CommandLine {
    auto const argsBackend = mainArgs(inputFile);
    auto const args = toCharConstVector(argsBackend);
    return fw::greeter::CommandLine{static_cast<int>(args.size()), args.data(),
                                    standardOutput_, standardError_};
  }

  std::ostringstream standardOutput_{};
  std::ostringstream standardError_{};

 private:
  auto mainArgs(std::filesystem::path const& inputFile)
      -> std::vector<std::string> {
    return {"argv[0] is don't care", "--input_file=" + inputFile.string()};
  }

  auto toCharConstVector(std::vector<std::string> const& input)
      -> std::vector<char const*> {
    auto result = std::vector<char const*>(input.size(), nullptr);

    for (auto i = 0; i < input.size(); i++) {
      result[i] = input[i].c_str();
    }

    return result;
  }
};

TEST_F(
    ApplicationIntegrationTest,
    GivenValidFileWithThreeEntriesWhenRunThenExpectedResultIsWrittenToOutputStream) {
  // Arrange
  auto cli = createCli(std::filesystem::current_path() / ".." / ".." / "data" /
                       "personal_name.in");
  auto const sut = Application{cli};
  auto const expected = R"(Wolfgang Amadeus Mozart
Kurt Donald Cobain
James Hetfield
)";

  // Act
  auto const exitCode = sut.run();

  // Assert
  ASSERT_EQ(0, exitCode);
  ASSERT_TRUE(standardError_.str().empty());
  ASSERT_EQ(expected, standardOutput_.str());
}

TEST_F(
    ApplicationIntegrationTest,
    GivenInputFileDoesNotExistWhenRunThenExpectedTextIsWrittenToErrorStream) {
  // Arrange
  auto cli = createCli("/does/not/exist.in");
  auto const sut = Application{cli};

  // Act
  auto const exitCode = sut.run();

  // Assert
  ASSERT_EQ(1, exitCode);
  ASSERT_TRUE(standardOutput_.str().empty());
  ASSERT_EQ(
      "Exception in fw::greeter::Application: The input file "
      "\"/does/not/exist.in\" does not exist\n",
      standardError_.str());
}

}  // namespace
