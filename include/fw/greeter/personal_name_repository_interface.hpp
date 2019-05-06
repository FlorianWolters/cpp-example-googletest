/// @file
/// Declares the `fw::greeter::PersonalNameRepositoryInterface` *Interface
/// Class*.
///
/// @author Florian Wolters <wolters.fl@gmail.com>
/// @copyright Copyright (c) 2019, Florian Wolters and/or its affiliates.
/// All rights reserved.
/// This code is licensed under the MIT License. See `LICENSE` file for details.

#ifndef FW_GREETER_PERSONAL_REPOSITORY_INTERFACE_HPP_
#define FW_GREETER_PERSONAL_REPOSITORY_INTERFACE_HPP_

// Standard Library
#include <vector>

#include <fw/greeter/personal_name.hpp>

namespace fw {
namespace greeter {

class PersonalNameRepositoryInterface {
 public:
  /// Finalizes an instance of the `PersonalNameRepositoryInterface` class.
  virtual ~PersonalNameRepositoryInterface() = default;

  virtual auto findAll() const -> std::vector<PersonalName> = 0;
};

}  // namespace greeter
}  // namespace fw

#endif  // FW_GREETER_PERSONAL_REPOSITORY_INTERFACE_HPP_
