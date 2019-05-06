/// @file
/// Declares the `fw::io::InputStreamUtil` *Utility Class*.
///
/// @author Florian Wolters <wolters.fl@gmail.com>
/// @copyright Copyright (c) 2019, Florian Wolters and/or its affiliates.
/// All rights reserved.
/// This code is licensed under the MIT License. See `LICENSE` file for details.

#ifndef FW_IO_INPUT_STREAM_UTIL_HPP_
#define FW_IO_INPUT_STREAM_UTIL_HPP_

#include <fw/io/input_stream_util_interface.hpp>

namespace fw {
namespace io {

class InputStreamUtil final : public InputStreamUtilInterface {
 public:
  static auto instance() -> InputStreamUtil const& {
    static auto instance = InputStreamUtil{};
    return instance;
  }

  auto string(std::istream& is) const -> std::string override {
    auto oss = std::ostringstream{};
    oss << is.rdbuf();
    return oss.str();
  }

 private:
  InputStreamUtil() = default;
};

}  // namespace io
}  // namespace fw

#endif  // FW_IO_INPUT_STREAM_UTIL_HPP_
