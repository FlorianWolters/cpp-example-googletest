/// @file
/// Declares the `fw::greeter::testing::CommandLineMock` *Test Double* class.
///
/// @author Florian Wolters <wolters.fl@gmail.com>
/// @copyright Copyright (c) 2019, Florian Wolters and/or its affiliates.
/// All rights reserved.
/// This code is licensed under the MIT License. See `LICENSE` file for details.

#ifndef FW_GREETER_TESTING_COMMAND_LINE_MOCK_HPP_
#define FW_GREETER_TESTING_COMMAND_LINE_MOCK_HPP_

// Google Test
#include <gmock/gmock.h>

#include <fw/greeter/command_line_interface.hpp>

namespace fw {
namespace greeter {
namespace testing {

class CommandLineMock : public CommandLineInterface {
 public:
  MOCK_METHOD0(parse, void());
  MOCK_METHOD0(config, ConfigInterface&());
  MOCK_METHOD0(standardOutput, std::ostream&());
  MOCK_METHOD0(standardError, std::ostream&());
};

}  // namespace testing
}  // namespace greeter
}  // namespace fw

#endif  // FW_GREETER_TESTING_COMMAND_LINE_MOCK_HPP_
