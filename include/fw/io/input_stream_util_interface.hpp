/// @file
/// Declares the `fw::io::InputStreamUtilInterface` *Interface Class*.
///
/// @author Florian Wolters <wolters.fl@gmail.com>
/// @copyright Copyright (c) 2019, Florian Wolters and/or its affiliates.
/// All rights reserved.
/// This code is licensed under the MIT License. See `LICENSE` file for details.

#ifndef FW_IO_INPUT_STREAM_UTIL_INTERFACE_HPP_
#define FW_IO_INPUT_STREAM_UTIL_INTERFACE_HPP_

// Standard Library
#include <istream>
#include <string>

namespace fw {
namespace io {

class InputStreamUtilInterface {
 public:
  /// Finalizes an instance of the `InputStreamUtilInterface` class.
  virtual ~InputStreamUtilInterface() = default;

  virtual auto string(std::istream& is) const -> std::string = 0;
};

}  // namespace io
}  // namespace fw

#endif  // FW_IO_INPUT_STREAM_UTIL_INTERFACE_HPP_
