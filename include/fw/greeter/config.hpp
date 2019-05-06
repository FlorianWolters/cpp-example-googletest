/// @file
/// Declares the `fw::greeter::Config` concrete class.
///
/// @author Florian Wolters <wolters.fl@gmail.com>
/// @copyright Copyright (c) 2019, Florian Wolters and/or its affiliates.
/// All rights reserved.
/// This code is licensed under the MIT License. See `LICENSE` file for details.

#ifndef FW_GREETER_CONFIG_HPP_
#define FW_GREETER_CONFIG_HPP_

// Standard Library
#include <filesystem>
#include <memory>
#include <utility>

#include <fw/exception.hpp>
#include <fw/invalid_argument.hpp>

#include <fw/greeter/config_interface.hpp>
#include <fw/greeter/personal_name_repository_interface.hpp>
#include <fw/greeter/text_file_personal_name_repository.hpp>

namespace fw {
namespace greeter {

class Config final : public ConfigInterface {
 public:
  enum class DataSource : int { AsciiFile = 0 };

  explicit Config(DataSource const dataSource,
                  std::filesystem::path inputFilePath)
      : dataSource_{dataSource},
        inputFilePath_{std::move(inputFilePath)},
        personalNameRepository_{createPersonalNameRepository()} {
    throwIfInputFilePathDoesNotExist();
  }

  auto personalNameRepository() -> PersonalNameRepositoryInterface& override {
    return *personalNameRepository_;
  }

 private:
  auto createPersonalNameRepository() const
      -> std::unique_ptr<PersonalNameRepositoryInterface> {
    switch (dataSource_) {
      case Config::DataSource::AsciiFile:
        return std::make_unique<fw::greeter::TextFilePersonalNameRepository>(
            inputFilePath_);
      default:
        throw Exception{"Unsupported fw::greeter::Config::DataSource"};
    }
  }

  auto throwIfInputFilePathDoesNotExist() const -> void {
    if (!std::filesystem::exists(inputFilePath_)) {
      throw InvalidArgument{"The input file \"" + inputFilePath_.string() +
                            "\" does not exist"};
    }
  }

  DataSource dataSource_;
  std::filesystem::path inputFilePath_;
  std::unique_ptr<PersonalNameRepositoryInterface> personalNameRepository_;
};

}  // namespace greeter
}  // namespace fw

#endif  // FW_GREETER_CONFIG_HPP_
