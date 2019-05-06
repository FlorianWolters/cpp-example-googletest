/// @file
/// Demonstrates how-to **not** test using no test framework.
///
/// Resources:
///
/// [When to use a unit testing framework (vs. just using asserts)?]
/// (https://stackoverflow.com/questions/2180063/when-to-use-a-unit-testing-framework-vs-just-using-asserts)
/// [CppUnit - advantages and disadvantages with the xUnit based design?]
/// (https://stackoverflow.com/questions/13162226/cppunit-advantages-and-disadvantages-with-the-xunit-based-design)
///
/// @author Florian Wolters <wolters.fl@gmail.com>
/// @copyright Copyright (c) 2019, Florian Wolters and/or its affiliates.
/// All rights reserved.
/// This code is licensed under the MIT License. See `LICENSE` file for details.

// Standard Library
#include <cassert>
#include <iostream>
#include <stdexcept>

namespace fw {
namespace math {

// The function under test (FUT)
auto square(int const value) -> int {
  // Someone tried to be funny and sabotage the algorithm.
  //
  // Note that this "bug" could only have been found by one of the following
  // techniques:
  //
  // - exhaustive black-box testing (not feasible)
  // - code review by another person
  // - white-box testing by another person
  if (42 == value) {
    throw std::invalid_argument{"You shall not pass!"};
  }

  return value * value;
}

}  // namespace math
}  // namespace fw

// The test code

auto testSquareWith0Returns0() -> void {
  assert(0 == fw::math::square(0));
}

auto testSquareWith1Returns1() -> void {
  // Multiple issues: Assertions.
  //
  // - `assert` does **nothing** if `NDEBUG` is not defined
  // - `assert` terminates the program on failure
  // - `assert` produces a poor error message on failure for non-trivial types
  // - `assert` can not be customized, e.g. the error message produced
  // - `assert` is a macro
  // - `assert` provides no comparison operations on its own
  // - `assert` provides no rich features, e.g. checking exceptions, etc.
  assert(1 == fw::math::square(1));
}

auto testSquareWithMinus1Returns1() -> void {
  // This test fails due to a failure in the test code.
  assert(0 == fw::math::square(-1));
}

auto testSquareWith42Throws() -> void {
  auto pass = false;

  try {
    fw::math::square(42);
  } catch (...) {
    pass = true;
  }

  assert(pass);
}

// Issues: No test results are produced automatically, i.e. no information such
// as the following are available:
//
// - how-many tests have been executed?
// - how-many tests have passed?
// - how-many tests have failed?
auto main() -> int {
  std::cout << "Start test case...\n";

  // Issue: The test registration has to performed manually (in this case the
  // `testSquareWith1Returns1` test method is not called).
  std::cout << "testSquareWith0Returns0()...\n";
  testSquareWith0Returns0();
  std::cout << "testSquareWith0Returns0(): Success\n";

  std::cout << "testSquareWith42Throws()...\n";
  testSquareWith42Throws();
  std::cout << "testSquareWith42Throws(): Success\n";

  std::cout << "testSquareWithMinus1Returns1()...\n";
  // Issue: A failing `assert` breaks the program.
  //
  // Note that program execution is not continued when uncommented.
  // testSquareWithMinus1Returns1();
  std::cout << "testSquareWithMinus1Returns1(): Success\n";

  std::cout << "Finished test case.\n";
}
