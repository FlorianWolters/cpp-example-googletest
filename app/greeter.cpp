/// @file
/// Contains the `main` entry-point function for the *Greeter* application.
///
/// @author Florian Wolters <wolters.fl@gmail.com>
/// @copyright Copyright (c) 2019, Florian Wolters and/or its affiliates.
/// All rights reserved.
/// This code is licensed under the MIT License. See `LICENSE` file for details.

#include <fw/greeter/application.hpp>
#include <fw/greeter/command_line.hpp>

/// Runs the *Greeter* application.
///
/// @param argc the number of command-line interface arguments
/// @param argv the command-line interface arguments
///
/// @return `0` on success or `1` on failure
auto main(int const argc, char const* const argv[]) -> int {
  auto cli = fw::greeter::CommandLine{argc, argv};

  // The *Factory* for the *Repository* that allows querying `PersonalName`
  // instances from an ASCII file is injected here in order to be able to unit
  // test the `fw::greeter::Application` class.
  return fw::greeter::Application{cli}.run();
}
