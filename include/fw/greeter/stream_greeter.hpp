/// @file
/// Declares the `fw::greeter::StreamGreeter` concrete class.
///
/// @author Florian Wolters <wolters.fl@gmail.com>
/// @copyright Copyright (c) 2019, Florian Wolters and/or its affiliates.
/// All rights reserved.
/// This code is licensed under the MIT License. See `LICENSE` file for details.

#ifndef FW_GREETER_STREAM_GREATER_HPP_
#define FW_GREETER_STREAM_GREATER_HPP_

// Standard Library
#include <ostream>

#include <fw/greeter/greeter_interface.hpp>

namespace fw {
namespace greeter {

class StreamGreater final : public GreeterInterface {
 public:
  explicit StreamGreater(std::ostream& stream) : stream_{stream} {
    // NOOP
  }

  auto greet(PersonalName const& personalName) const -> void override {
    stream_ << personalName << '\n';
  }

 private:
  std::ostream& stream_;
};

}  // namespace greeter
}  // namespace fw

#endif  // FW_GREETER_STREAM_GREATER_HPP_
