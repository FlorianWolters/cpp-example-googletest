include_guard()

find_program(ReportGenerator_EXECUTABLE
  ReportGenerator
  PATHS
    ENV REPORTGENERTOR_HOME
    ENV REPORTGENERTOR_ROOT
  PATH_SUFFIXES
    net47
  )

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(ReportGenerator ReportGenerator_EXECUTABLE)

if(ReportGenerator_FOUND AND
   NOT TARGET ReportGenerator::exe)
  add_executable(ReportGenerator::exe IMPORTED)
endif()

mark_as_advanced(ReportGenerator_EXECUTABLE)
