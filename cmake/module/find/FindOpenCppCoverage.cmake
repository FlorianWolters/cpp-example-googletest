include_guard()

find_program(OpenCppCoverage_EXECUTABLE
  OpenCppCoverage
  PATHS
    ENV OPENCPPCOVERAGE_HOME
    ENV OPENCPPCOVERAGE_ROOT
  )

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(OpenCppCoverage OpenCppCoverage_EXECUTABLE)

if(OpenCppCoverage_FOUND AND
   NOT TARGET OpenCppCoverage::exe)
  add_executable(OpenCppCoverage::exe IMPORTED)
endif()

mark_as_advanced(OpenCppCoverage_EXECUTABLE)
