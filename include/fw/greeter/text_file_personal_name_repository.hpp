/// @file
/// Declares the `fw::greeter::TextFilePersonalNameRepository` concrete class.
///
/// @author Florian Wolters <wolters.fl@gmail.com>
/// @copyright Copyright (c) 2019, Florian Wolters and/or its affiliates.
/// All rights reserved.
/// This code is licensed under the MIT License. See `LICENSE` file for details.

#ifndef FW_GREETER_TEXT_FILE_PERSONAL_REPOSITORY_HPP_
#define FW_GREETER_TEXT_FILE_PERSONAL_REPOSITORY_HPP_

// Standard Library
#include <filesystem>
#include <utility>

#include <fw/greeter/personal_name_repository_interface.hpp>

#include <fw/string_util.hpp>

#include <fw/io/input_stream_util.hpp>

namespace fw {
namespace greeter {

class TextFilePersonalNameRepository final
    : public PersonalNameRepositoryInterface {
 public:
  explicit TextFilePersonalNameRepository(std::filesystem::path filePath)
      : filePath_{std::move(filePath)} {
    // NOOP
  }

  // Inherited via fw::greeter::PersonalNameRepository
  auto findAll() const -> std::vector<PersonalName> override {
    auto personalNames = std::vector<PersonalName>{};

    auto fileStream = std::ifstream{filePath_};
    auto const fileContent = io::InputStreamUtil::instance().string(fileStream);
    auto const fileLines = StringUtil::instance().split(fileContent, '\n');

    for (auto const& fileLine : fileLines) {
      personalNames.emplace_back(fileLine);
    }

    return personalNames;
  }

 private:
  std::filesystem::path filePath_;
};

}  // namespace greeter
}  // namespace fw

#endif  // FW_GREETER_TEXT_FILE_PERSONAL_REPOSITORY_HPP_
