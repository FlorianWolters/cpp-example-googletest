/// @file
/// Declares the `fw::StringUtil` *Utility Class*.
///
/// @author Florian Wolters <wolters.fl@gmail.com>
/// @copyright Copyright (c) 2019, Florian Wolters and/or its affiliates.
/// All rights reserved.
/// This code is licensed under the MIT License. See `LICENSE` file for details.

#ifndef FW_STRING_UTIL_HPP_
#define FW_STRING_UTIL_HPP_

// Standard Library
#include <iterator>
#include <sstream>

#include <fw/string_util_interface.hpp>

namespace fw {

class StringUtil final : StringUtilInterface {
 public:
  static auto instance() -> StringUtil const& {
    static auto instance = StringUtil{};
    return instance;
  }

  auto split(std::string const& str) const
      -> std::vector<std::string> override {
    auto iss = std::istringstream{str};
    return std::vector<std::string>((std::istream_iterator<std::string>(iss)),
                                    std::istream_iterator<std::string>());
  }

  auto split(std::string const& str, char const delimiter) const
      -> std::vector<std::string> override {
    auto tokens = std::vector<std::string>{};
    auto token = std::string{};
    auto tokenStream = std::istringstream{str};

    while (std::getline(tokenStream, token, delimiter)) {
      tokens.push_back(token);
    }

    return tokens;
  }

 private:
  StringUtil() = default;
};

}  // namespace fw

#endif  // FW_STRING_UTIL_HPP_
