/// @file
/// Declares the `fw::greeter::CommandLineInterface` *Interface Class*.
///
/// @author Florian Wolters <wolters.fl@gmail.com>
/// @copyright Copyright (c) 2019, Florian Wolters and/or its affiliates.
/// All rights reserved.
/// This code is licensed under the MIT License. See `LICENSE` file for details.

#ifndef FW_GREETER_COMMAND_LINE_INTERFACE_HPP_
#define FW_GREETER_COMMAND_LINE_INTERFACE_HPP_

// Standard Library
#include <iosfwd>

#include <fw/greeter/config_interface.hpp>

namespace fw {
namespace greeter {

class CommandLineInterface {
 public:
  /// Finalizes an instance of the `CommandLineInterface` class.
  virtual ~CommandLineInterface() = default;

  virtual auto parse() -> void = 0;

  virtual auto config() -> ConfigInterface& = 0;

  virtual auto standardOutput() -> std::ostream& = 0;

  virtual auto standardError() -> std::ostream& = 0;
};

}  // namespace greeter
}  // namespace fw

#endif  // FW_GREETER_COMMAND_LINE_INTERFACE_HPP_
