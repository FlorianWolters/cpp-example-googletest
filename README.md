# cpp-example-googletest

Example project that demonstrates how-to use the Google Test C++ test framework
in a modern Convention-over-Configuration (CoC) C++ Open-Source Software (OSS)
ecosystem.

**Work in Progress:** Refer to the section TODO List below.

## Dependencies

- Build System Generator: CMake >= v3.13.1
- Build System: Ninja >= v1.9.0
- C++ Package Manager: vcpkg >= 2018.11.23
- Code Coverage Tool:
  - OpenCppCoverage >= v0.9.7.0
  - ReportGenerator >= v4.1.5
- C++ Libraries (via `vcpkg`)
  - Testing
    - Test Framework: Google Test >= 2019-01-04-2
    - Mock Object Framework: Google Mock >= 2019-01-04-2
  - Production
    - docopt >= 2018-11-01
    - fmt >= 5.3.0-1

The following Integrated Development Environment (IDE) tools have been used for
development, though other work as well:

- IDE: Visual Studio Community 2019 v16.0.3
- Test Adapter for Google Test v0.10.1.8
- Clang Power Tools v4.10.3

## TODO List

- Add additional Google Test Features:
  - Custom assertions.
  - Custom matchers.
- Clean up build system:
  - Remove compiler warnings.
  - Create CMake module for OpenCppCoverage.
  - Create CMake module for ReportGenerator.
- Document public API with Doxygen.
- Add Continuous Integration (CI) support for cloud services:
  - AppVeyor
  - Travis CI
  - Jenkins

## Credits

* [Florian Wolters](https://github.com/FlorianWolters)
* [All Contributors](https://github.com/FlorianWolters/cpp-example-googletest/contributors)

## License

MIT License

Copyright (c) 2019 Florian Wolters

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
