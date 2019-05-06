/// @file
/// Declares the `fw::StringUtilInterface` *Interface Class*.
///
/// @author Florian Wolters <wolters.fl@gmail.com>
/// @copyright Copyright (c) 2019, Florian Wolters and/or its affiliates.
/// All rights reserved.
/// This code is licensed under the MIT License. See `LICENSE` file for details.

#ifndef FW_STRING_UTIL_INTERFACE_HPP_
#define FW_STRING_UTIL_INTERFACE_HPP_

// Standard Library
#include <string>
#include <vector>

namespace fw {

class StringUtilInterface {
 public:
  /// Finalizes an instance of the `StringUtilInterface` class.
  virtual ~StringUtilInterface() = default;

  virtual auto split(std::string const& text) const
      -> std::vector<std::string> = 0;

  virtual auto split(std::string const& str, char const delimiter) const
      -> std::vector<std::string> = 0;
};

}  // namespace fw

#endif  // FW_STRING_UTIL_INTERFACE_HPP_
