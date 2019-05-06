/// @file
/// Declares the `fw::greeter::GreeterInterface` *Interface Class*.
///
/// @author Florian Wolters <wolters.fl@gmail.com>
/// @copyright Copyright (c) 2019, Florian Wolters and/or its affiliates.
/// All rights reserved.
/// This code is licensed under the MIT License. See `LICENSE` file for details.

#ifndef FW_GREETER_GREETER_INTERFACE_HPP_
#define FW_GREETER_GREETER_INTERFACE_HPP_

#include <fw/greeter/personal_name.hpp>

namespace fw {
namespace greeter {

class GreeterInterface {
 public:
  /// Finalizes an instance of the `GreeterInterface` class.
  virtual ~GreeterInterface() = default;

  virtual auto greet(PersonalName const& personalName) const -> void = 0;
};

}  // namespace greeter
}  // namespace fw

#endif  // FW_GREETER_GREETER_INTERFACE_HPP_
