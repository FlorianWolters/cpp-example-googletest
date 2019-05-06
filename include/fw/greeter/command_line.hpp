/// @file
/// Declares the `fw::greeter::CommandLine` concrete class.
///
/// @author Florian Wolters <wolters.fl@gmail.com>
/// @copyright Copyright (c) 2019, Florian Wolters and/or its affiliates.
/// All rights reserved.
/// This code is licensed under the MIT License. See `LICENSE` file for details.

#ifndef FW_GREETER_COMMAND_LINE_HPP_
#define FW_GREETER_COMMAND_LINE_HPP_

// Standard Library
#include <optional>
#include <ostream>
#include <string>
#include <vector>

// docopt
#include <docopt/docopt.h>

#include <fw/greeter/command_line_interface.hpp>
#include <fw/greeter/config.hpp>

namespace fw {
namespace greeter {

constexpr char USAGE[] =
    R"(Greeter - Greets one or more persons by their personal name that is stored in a file.

    Usage:
      greeter --input_file=<file>
      greeter (-h | --help)
      greeter (-v | --version)

    Options:
      -h --help             Show this screen.
      -v --version          Show version.
      --input_file=<file>   The input file.
)";

class CommandLine final : public CommandLineInterface {
 public:
  explicit CommandLine(int const argc, char const* const argv[])
      : CommandLine{argc, argv, std::cout, std::cerr} {
    // NOOP
  }

  explicit CommandLine(int const argc,
                       char const* const argv[],
                       std::ostream& standardOutput,
                       std::ostream& standardError)
      : argv_((argv + 1), (argv + argc)),
        standardOutput_{standardOutput},
        standardError_{standardError},
        config_{} {
    // NOOP
  }

  auto parse() -> void override {
    auto const showHelpIfRequested = true;
    auto const optionsFirst = false;
    auto const args = docopt::docopt(USAGE, argv_, showHelpIfRequested,
                                     "Greeter v0.1.0", optionsFirst);

    config_ = Config{Config::DataSource::AsciiFile,
                     std::filesystem::path{args.at("--input_file").asString()}};
  }

  auto config() -> ConfigInterface& override {
    if (!config_.has_value()) {
      throw Exception{"fw::greeter::Config::parse has not been called"};
    }

    return config_.value();
  }

  auto standardOutput() -> std::ostream& override { return standardOutput_; }

  auto standardError() -> std::ostream& override { return standardError_; }

 private:
  std::vector<std::string> argv_;
  std::ostream& standardOutput_;
  std::ostream& standardError_;
  std::optional<Config> config_;
};

}  // namespace greeter
}  // namespace fw

#endif  // FW_GREETER_COMMAND_LINE_HPP_
