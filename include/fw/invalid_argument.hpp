/// @file
/// Declares the `fw::InvalidArgument` exception class.
///
/// @author Florian Wolters <wolters.fl@gmail.com>
/// @copyright Copyright (c) 2019, Florian Wolters and/or its affiliates.
/// All rights reserved.
/// This code is licensed under the MIT License. See `LICENSE` file for details.

#ifndef FW_INVALID_ARGUMENT_HPP_
#define FW_INVALID_ARGUMENT_HPP_

#include <fw/exception.hpp>

namespace fw {

class InvalidArgument final : public Exception {
  using Exception::Exception;
};

}  // namespace fw

#endif  // FW_INVALID_ARGUMENT_HPP_
