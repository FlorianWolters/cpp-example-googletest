/// @file
/// Declares the `fw::greeter::PersonalName` concrete class.
///
/// @author Florian Wolters <wolters.fl@gmail.com>
/// @copyright Copyright (c) 2019, Florian Wolters and/or its affiliates.
/// All rights reserved.
/// This code is licensed under the MIT License. See `LICENSE` file for details.

#ifndef FW_GREETER_PERSONAL_NAME_HPP_
#define FW_GREETER_PERSONAL_NAME_HPP_

// Standard Library
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <utility>

// fmt
#include <fmt/format.h>

#include <fw/invalid_argument.hpp>
#include <fw/string_util.hpp>

namespace fw {
namespace greeter {

class PersonalName final {
 public:
  explicit PersonalName(std::string const& full) {
    auto const parts = StringUtil::instance().split(full);

    if (2 == parts.size()) {
      first_ = parts.at(0);
      last_ = parts.at(1);
    } else if (3 == parts.size()) {
      first_ = parts.at(0);
      middle_ = parts.at(1);
      last_ = parts.at(2);
    } else {
      throw InvalidArgument{
          "fw::greeter::PersonalName: the 'full' argument does not contain at "
          "least a first and last name (is: \"" +
          full + "\")"};
    }
  }

  explicit PersonalName(std::string first, std::string middle, std::string last)
      : first_{std::move(first)},
        middle_{std::move(middle)},
        last_{std::move(last)} {
    throwIfFirstIsEmpty();
    throwIfLastIsEmpty();
  }

  auto first() const -> std::string_view { return first_; }

  auto middle() const -> std::string_view { return middle_; }

  auto last() const -> std::string_view { return last_; }

  auto full() const -> std::string {
    if (middle_.empty()) {
      return fmt::format("{} {}", first_, last_);
    } else {
      return fmt::format("{} {} {}", first_, middle_, last_);
    }
  }

 private:
  auto throwIfFirstIsEmpty() const -> void {
    if (first_.empty()) {
      throw InvalidArgument{
          "fw::greeter::PersonalName: the 'first' argument may not be empty"};
    }
  }

  auto throwIfLastIsEmpty() const -> void {
    if (last_.empty()) {
      throw InvalidArgument{
          "fw::greeter::PersonalName: the 'last' argument may not be empty"};
    }
  }

  std::string first_;
  std::string middle_;
  std::string last_;
};

inline auto operator<<(std::ostream& os, PersonalName const& personalName)
    -> std::ostream& {
  os << personalName.full();
  return os;
}

}  // namespace greeter
}  // namespace fw

#endif  // FW_GREETER_PERSONAL_NAME_HPP_
