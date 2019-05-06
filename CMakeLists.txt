cmake_minimum_required(VERSION 3.13.1)

list(APPEND CMAKE_MODULE_PATH
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/module"
  "${CMAKE_CURRENT_SOURCE_DIR}/cmake/module/find"
  )

# vcpkg integration
#
# This build system hides the package manager configuration from the user.
# If using vcpkg directly the modification of the following CMake variables is mandatory:
#
# - `CMAKE_TOOLCHAIN_FILE`
# - `VCPKG_CHAINLOAD_TOOLCHAIN_FILE`
# - `VCPKG_TARGET_TRIPLET`

# TODO(2019-05-05 by wolters): These three variables belong into the yaml configuration file.
set(CEVOKE_PACKAGE_MANAGER_CXX "vcpkg" CACHE STRING "The C++ package manager to use (vcpkg, conan, hunter).")
set(CEVOKE_PACKAGE_MANAGER_VERSION "2018.11.23" CACHE INTERNAL "")
set(CEVOKE_PACKAGE_MANAGER_VCPKG_TRIPLET "x64-windows-static" CACHE INTERNAL "")

set(CEVOKE_PACKAGE_MANAGER_VCPKG_VERSION "2018.11.23" CACHE INTERNAL "")

message(STATUS "Using the C++ package manager \"${CEVOKE_PACKAGE_MANAGER_CXX}\"")

if(CEVOKE_PACKAGE_MANAGER_CXX STREQUAL "vcpkg")
  if(NOT DEFINED CEVOKE_PACKAGE_MANAGER_VERSION)
    set(CEVOKE_PACKAGE_MANAGER_VERSION ${CEVOKE_PACKAGE_MANAGER_VCPKG_VERSION})
  endif()

  find_package(vcpkg ${CEVOKE_PACKAGE_MANAGER_VERSION} REQUIRED MODULE)

  if((DEFINED CMAKE_TOOLCHAIN_FILE) AND
     (NOT ${CMAKE_TOOLCHAIN_FILE} STREQUAL ${vcpkg_CMAKE_TOOLCHAIN_FILE}))
    set(VCPKG_CHAINLOAD_TOOLCHAIN_FILE ${CMAKE_TOOLCHAIN_FILE} CACHE INTERNAL "")
  endif()

  set(CMAKE_TOOLCHAIN_FILE "${vcpkg_CMAKE_TOOLCHAIN_FILE}" CACHE INTERNAL "")

  if(DEFINED ENV{VCPKG_DEFAULT_TRIPLET} AND NOT DEFINED CEVOKE_PACKAGE_MANAGER_VCPKG_TRIPLET)
    message(STATUS "vcpkg target triplet configured by environment variable.")
    set(VCPKG_TARGET_TRIPLET "$ENV{VCPKG_DEFAULT_TRIPLET}" CACHE INTERNAL "")
  else()
    message(STATUS "vcpkg target triplet configured by CEvoke.")
    set(VCPKG_TARGET_TRIPLET ${CEVOKE_PACKAGE_MANAGER_VCPKG_TRIPLET} CACHE INTERNAL "")
  endif()
endif()

project(cpp-example-googletest
  VERSION 0.1.0
  LANGUAGES CXX
  )

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}"
  PREFIX "Build System"
  FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt"
    "${CMAKE_CURRENT_SOURCE_DIR}/CMakeSettings.json"
  )

# Production code

find_package(docopt REQUIRED CONFIG)
find_package(fmt REQUIRED CONFIG)

file(GLOB_RECURSE source_files_cxx_declaration
  LIST_DIRECTORIES false
  CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp"
  )
file(GLOB_RECURSE source_files_cxx_definition
  LIST_DIRECTORIES false
  CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
  )
file(GLOB_RECURSE source_files_cxx_declaration_test
  LIST_DIRECTORIES false
  CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/test/include/*.hpp"
  )
file(GLOB_RECURSE source_files_cxx_definition_test
  LIST_DIRECTORIES false
  CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/test/src/*.cpp"
  )

source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}/include"
  PREFIX "C++ Header Files"
  FILES ${source_files_cxx_declaration}
  )
source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}/src"
  PREFIX "C++ Source Files"
  FILES ${source_files_cxx_definition}
  )
source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}/test/include"
  PREFIX "C++ Header Files (Test)"
  FILES ${source_files_cxx_declaration_test}
  )
source_group(
  TREE "${CMAKE_CURRENT_SOURCE_DIR}/test/src"
  PREFIX "C++ Source Files (Test)"
  FILES ${source_files_cxx_definition_test}
  )

# Object library
add_library(${PROJECT_NAME} OBJECT)
set_target_properties(${PROJECT_NAME}
  PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED YES
  CXX_EXTENSIONS NO
  FOLDER "02. Library"
  )
target_sources(${PROJECT_NAME}
  PRIVATE
    ${source_files_cxx_definition}
    ${source_files_cxx_declaration}
  )
target_compile_definitions(${PROJECT_NAME}
  PUBLIC
    $<$<CXX_COMPILER_ID:MSVC>:_CRT_SECURE_NO_WARNINGS>
    $<$<CXX_COMPILER_ID:MSVC>:_SCL_SECURE_NO_WARNINGS>
    $<$<CXX_COMPILER_ID:MSVC>:NOMINMAX>
  )
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
target_compile_options(${PROJECT_NAME}
  PUBLIC
    $<$<CXX_COMPILER_ID:MSVC>:/W4>
	  $<$<CXX_COMPILER_ID:MSVC>:/permissive->
    $<$<CXX_COMPILER_ID:MSVC>:/MTd>
  )
target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	  $<INSTALL_INTERFACE:include>
  )
target_link_libraries(${PROJECT_NAME}
  PUBLIC
    docopt_s
    fmt::fmt
  )
# Normal library
add_library(${PROJECT_NAME}_-_normal)
target_link_libraries(${PROJECT_NAME}_-_normal
  PRIVATE ${PROJECT_NAME}
  )
target_sources(${PROJECT_NAME}_-_normal
  PRIVATE
    $<TARGET_OBJECTS:${PROJECT_NAME}>
)
set_target_properties(${PROJECT_NAME}_-_normal
  PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED YES
  CXX_EXTENSIONS NO
  FOLDER "02. Library"
  )

# Production executables
file(GLOB_RECURSE source_files_cxx_main_production
  LIST_DIRECTORIES false
  CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/app/*.cpp"
  )

foreach(source_file ${source_files_cxx_main_production})
  get_filename_component(target_name ${source_file} NAME_WE)
  add_executable(${target_name})
  add_custom_command(
    TARGET ${target_name} 
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/data" "${CMAKE_CURRENT_BINARY_DIR}/data"
    )
  set_target_properties(${target_name}
    PROPERTIES
      CXX_STANDARD 17
      CXX_STANDARD_REQUIRED YES
      CXX_EXTENSIONS NO
      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin"
      FOLDER "03. Application"
    )
  target_sources(${target_name} PRIVATE ${source_file})
  target_link_libraries(${target_name} PRIVATE ${PROJECT_NAME})
endforeach()

add_custom_target(cp_data_dir ALL
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/data ${CMAKE_BINARY_DIR}/data
  BYPRODUCTS ${CMAKE_BINARY_DIR}/data
  VERBATIM
  COMMENT "Copying data files..."
  )
set_target_properties(cp_data_dir PROPERTIES FOLDER cevoke)

# Test code
option(BUILD_TESTING "Whether to build test executables or not." ON)

if(NOT BUILD_TESTING)
  message("The building of tests is disabled. Configure with -DBUILD_TESTING:BOOL=ON to enable build of test executables.")
  return()
endif()

file(GLOB_RECURSE source_files_cxx_definition_test
  LIST_DIRECTORIES false
  CONFIGURE_DEPENDS
  "${CMAKE_CURRENT_SOURCE_DIR}/test/src/*.cpp"
  )

if(NOT source_files_cxx_definition_test)
  message("The project does not contain any test source files.")
  return()
endif()

find_package(GTest REQUIRED CONFIG)
enable_testing()
include(GoogleTest)

foreach(source_file ${source_files_cxx_definition_test})
	get_filename_component(target_name ${source_file} NAME_WE)

	add_executable(${target_name})
  set_target_properties(${target_name}
    PROPERTIES
      CXX_STANDARD 17
      CXX_STANDARD_REQUIRED YES
      CXX_EXTENSIONS NO
      RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin/test"
      FOLDER "01. Test"
    )
	target_sources(${target_name}
    PRIVATE
      ${source_file}
      ${source_files_cxx_declaration_test}
    )
	target_include_directories(${target_name}
    PRIVATE
      "${CMAKE_CURRENT_SOURCE_DIR}/test/include"
    )
	target_link_libraries(${target_name}
	  PRIVATE
		  ${PROJECT_NAME}
		  GTest::gmock_main
	  )
  gtest_discover_tests(${target_name})
  list(APPEND CEVOKE_TEST_TARGETS ${target_name})
endforeach()



option(CEVOKE_BUILD_TESTING_COVERAGE "Whether to enable code coverage for test executables." ON)

if(NOT CEVOKE_BUILD_TESTING_COVERAGE)
  message("The building of test coverage is disabled. Configure with -DCEVOKE_BUILD_TESTING_COVERAGE:BOOL=ON to enable code coverage for test executables.")
  return()
endif()

# TODO(2019-05-05 by wolters): Add support for other code coverage tools.
find_package(OpenCppCoverage 0.9.7 REQUIRED MODULE)

set(opencppcoverage_output_dir "${CMAKE_CURRENT_BINARY_DIR}/OpenCppCoverage")
list(APPEND opencppcoverage_source_paths
  "${CMAKE_CURRENT_SOURCE_DIR}/app"
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
  "${CMAKE_CURRENT_SOURCE_DIR}/src"
  )

if(WIN32)
  string(REPLACE / \\ opencppcoverage_output_dir ${opencppcoverage_output_dir})

  foreach(source_path ${opencppcoverage_source_paths})
    string(REPLACE / \\ source_path ${source_path})
    list(APPEND opencppcoverage_sources_args --sources ${source_path})
  endforeach()
endif()

foreach(test_target_name ${CEVOKE_TEST_TARGETS})
  set(html_output_dir_path "${opencppcoverage_output_dir}\\${test_target_name}")
  set(cobertura_output_file_path "${opencppcoverage_output_dir}\\${test_target_name}_cobertura.xml")
  set(binary_output_file_path "${opencppcoverage_output_dir}\\${test_target_name}.cov")

  set(test_coverage_target_name "${test_target_name}_cov")
  add_custom_target(${test_coverage_target_name}
      ${OpenCppCoverage_EXECUTABLE}
      --quiet
	    ${opencppcoverage_sources_args}
      --export_type html:${html_output_dir_path}
      --export_type cobertura:${cobertura_output_file_path}
      --export_type binary:${binary_output_file_path}
      --continue_after_cpp_exception
	    -- $<TARGET_FILE:${test_target_name}>
      --gtest_shuffle
      --gtest_color=no
      --gtest_print_time=0
      --gtest_output=xml:${CMAKE_CURRENT_BINARY_DIR}/OpenCppCoverage/${test_target_name}_test_detail.xml
      # Ignore the exit code of OpenCppCoverage.
      > nul 2>&1 & set ERRORLEVEL=0
    BYPRODUCTS
      ${html_output_dir_path}
      ${cobertura_output_file_path}
      ${binary_output_file_path}
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin/test"
    COMMENT "Generating code coverage report for test executable ${test_target_name}..."
    # Attention: Do not use the `VERBATIM` option, otherwise the exit code is not ignored.
    )
  set_target_properties(${test_coverage_target_name} PROPERTIES FOLDER "01. Test/Coverage")

  list(APPEND opencppcoverage_input_coverage_args
    --input_coverage ${binary_output_file_path}
    )
  list(APPEND CEVOKE_TEST_COVERAGE_TARGETS ${test_coverage_target_name})
endforeach()

add_custom_target(test_cov
    ${OpenCppCoverage_EXECUTABLE}
    --quiet
    ${opencppcoverage_input_coverage_args}
    --export_type html:${opencppcoverage_output_dir}\\aggregated
    --export_type cobertura:${opencppcoverage_output_dir}\\aggregated_cobertura.xml
  BYPRODUCTS
    ${opencppcoverage_output_dir}\\aggregated
    ${opencppcoverage_output_dir}\\aggregated_cobertura.xml
  WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin/test"
  COMMENT "Creates an aggregated code coverage report for all test executables with OpenCppCoverage."
  )
set_target_properties(test_cov PROPERTIES FOLDER "01. Test/Coverage")

foreach(target_name ${CEVOKE_TEST_COVERAGE_TARGETS})
  add_dependencies(test_cov ${target_name})
endforeach()

find_package(ReportGenerator 4.1.5 REQUIRED MODULE)

function(cevoke_reportgenerator_add_target)
  set(options)
  set(oneValueArgs TARGET REPORT_TYPE TARGET_DIR HISTORY_DIR VERBOSITY FOLDER)
  set(multiValueArgs INPUT_REPORT_FILES)
  cmake_parse_arguments(args "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

  if(NOT args_VERBOSITY)
    set(args_VERBOSITY "Warning")
  endif()

  if(args_HISTORY_DIR)
    set(historydir_cli_arg "-historydir:${args_HISTORY_DIR}")
  endif()

  # TODO(2019-05-05 by wolters): Replace semicolon in reports list.
  # TODO(2019-05-05 by wolters): Only re-create report if input file has changed: https://stackoverflow.com/a/8236157/891439
  add_custom_command(
    OUTPUT ${args_TARGET_DIR}
    COMMAND ${ReportGenerator_EXECUTABLE}
      -reports:${args_INPUT_REPORT_FILES}
      -targetdir:${args_TARGET_DIR}
      -reporttypes:${args_REPORT_TYPE}
      ${historydir_cli_arg}
      -assemblyfilters:+*
      -classfilters:+*
      -filefilters:+*
      -verbosity:${args_VERBOSITY}
    DEPENDS ${args_INPUT_REPORT_FILES}
    WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin/test"
    COMMENT "Creates an aggregated code coverage report for all test executables with ReportGenerator."
    VERBATIM
  )

  add_custom_target(${args_TARGET} DEPENDS ${args_TARGET_DIR})
  set_target_properties(${args_TARGET} PROPERTIES FOLDER ${args_FOLDER})
endfunction()

function(cevoke_reportgenerator_add_targets)
  set(options)
  set(oneValueArgs TARGET_PREFIX REPORT_TYPE OUTPUT_DIR FOLDER)
  set(multiValueArgs REPORT_TYPES INPUT_REPORT_FILES)
  cmake_parse_arguments(args "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

  if(NOT args_REPORT_TYPES)
    set(args_REPORT_TYPES
      HTML
      HTMLSummary
      HTMLInline
      HtmlInline_AzurePipelines
      HtmlInline_AzurePipelines_Dark
      HTMLChart
      MHTML
      Cobertura
      SonarQube
      XML
      XMLSummary
      Latex
      LatexSummary
      #TeamCitySummary
      TextSummary
      CsvSummary
      PngChart
      Badges
      )
  endif()

  add_custom_target(${args_TARGET_PREFIX}
    COMMENT "Converts XML code coverage report into human readable reports in various formats."
  )
  set_target_properties(${args_TARGET_PREFIX} PROPERTIES FOLDER ${args_FOLDER})

  set(history_dir ${args_OUTPUT_DIR})

  foreach(report_type ${args_REPORT_TYPES})
    set(target_name "${args_TARGET_PREFIX}_${report_type}")
    cevoke_reportgenerator_add_target(
      TARGET ${target_name}
      REPORT_TYPE ${report_type}
      TARGET_DIR "${args_OUTPUT_DIR}/${report_type}"
      HISTORY_DIR ${history_dir}
      FOLDER ${args_FOLDER}
      INPUT_REPORT_FILES ${args_INPUT_REPORT_FILES}
      )
    add_dependencies(${args_TARGET_PREFIX} ${target_name})

    # Store persistent coverage information for the first report type only.
    set(history_dir)
  endforeach()
endfunction()

cevoke_reportgenerator_add_targets(
  TARGET_PREFIX "TestCoverageReportGenerator"
  OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/ReportGenerator"
  FOLDER "01. Test/Coverage/ReportGenerator"
  INPUT_REPORT_FILES "${opencppcoverage_output_dir}\\aggregated_cobertura.xml"
)
