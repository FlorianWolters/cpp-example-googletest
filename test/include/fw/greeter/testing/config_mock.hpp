/// @file
/// Declares the `fw::greeter::testing::ConfigMock` *Test Double* class.
///
/// @author Florian Wolters <wolters.fl@gmail.com>
/// @copyright Copyright (c) 2019, Florian Wolters and/or its affiliates.
/// All rights reserved.
/// This code is licensed under the MIT License. See `LICENSE` file for details.

#ifndef FW_GREETER_TESTING_CONFIG_MOCK_HPP_
#define FW_GREETER_TESTING_CONFIG_MOCK_HPP_

// Google Test
#include <gmock/gmock.h>

#include <fw/greeter/config_interface.hpp>

namespace fw {
namespace greeter {
namespace testing {

class ConfigMock : public ConfigInterface {
 public:
  MOCK_METHOD0(personalNameRepository, PersonalNameRepositoryInterface&());
};

}  // namespace testing
}  // namespace greeter
}  // namespace fw

#endif  // FW_GREETER_TESTING_CONFIG_MOCK_HPP_
