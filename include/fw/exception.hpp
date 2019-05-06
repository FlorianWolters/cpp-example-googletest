/// @file
/// Declares the `fw::Exception` exception class.
///
/// @author Florian Wolters <wolters.fl@gmail.com>
/// @copyright Copyright (c) 2019, Florian Wolters and/or its affiliates.
/// All rights reserved.
/// This code is licensed under the MIT License. See `LICENSE` file for details.

#ifndef FW_EXCEPTION_HPP_
#define FW_EXCEPTION_HPP_

// Standard Library
#include <stdexcept>

namespace fw {

class Exception : public std::runtime_error {
  using std::runtime_error::runtime_error;
};

}  // namespace fw

#endif  // FW_EXCEPTION_HPP_
