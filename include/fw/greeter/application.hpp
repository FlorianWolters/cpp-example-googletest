/// @file
/// Declares the `fw::greeter::Application` concrete class.
///
/// @author Florian Wolters <wolters.fl@gmail.com>
/// @copyright Copyright (c) 2019, Florian Wolters and/or its affiliates.
/// All rights reserved.
/// This code is licensed under the MIT License. See `LICENSE` file for details.

#ifndef FW_GREETER_APPLICATION_HPP_
#define FW_GREETER_APPLICATION_HPP_

// Standard Library
#include <fstream>
#include <memory>

#include <fw/string_util.hpp>

#include <fw/io/input_stream_util.hpp>

#include <fw/greeter/command_line_interface.hpp>
#include <fw/greeter/stream_greeter.hpp>

namespace fw {
namespace greeter {

class Application final {
 public:
  explicit Application(CommandLineInterface& cli) : cli_{cli} {
    // NOOP
  }

  auto run() const -> int {
    try {
      cli_.parse();
      return doRun();
    } catch (Exception const& ex) {
      cli_.standardError() << "Exception in fw::greeter::Application: "
                           << ex.what() << '\n';
      return EXIT_FAILURE;
    } catch (...) {
      cli_.standardError() << "Unknown exception in fw::greeter::Application\n";
      return EXIT_FAILURE;
    }
  }

 private:
  auto doRun() const -> int {
    auto const greeter = StreamGreater{cli_.standardOutput()};

    for (auto const& name : cli_.config().personalNameRepository().findAll()) {
      greeter.greet(name);
    }

    return EXIT_SUCCESS;
  }

  CommandLineInterface& cli_;
};

}  // namespace greeter
}  // namespace fw

#endif  // FW_GREETER_APPLICATION_HPP_
