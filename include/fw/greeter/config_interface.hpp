/// @file
/// Declares the `fw::greeter::ConfigInterface` *Interface Class*.
///
/// @author Florian Wolters <wolters.fl@gmail.com>
/// @copyright Copyright (c) 2019, Florian Wolters and/or its affiliates.
/// All rights reserved.
/// This code is licensed under the MIT License. See `LICENSE` file for details.

#ifndef FW_GREETER_CONFIG_INTERFACE_HPP_
#define FW_GREETER_CONFIG_INTERFACE_HPP_

#include <fw/greeter/personal_name_repository_interface.hpp>

namespace fw {
namespace greeter {

class ConfigInterface {
 public:
  /// Finalizes an instance of the `ConfigInterface` class.
  virtual ~ConfigInterface() = default;

  virtual auto personalNameRepository() -> PersonalNameRepositoryInterface& = 0;
};

}  // namespace greeter
}  // namespace fw

#endif  // FW_GREETER_CONFIG_INTERFACE_HPP_
