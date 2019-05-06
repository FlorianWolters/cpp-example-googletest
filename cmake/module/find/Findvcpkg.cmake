include_guard()

find_path(vcpkg_ROOT
  .vcpkg-root
  PATHS
    ${VCPKG_ROOT}
    ENV VCPKG_ROOT
)

find_program(vcpkg_EXECUTABLE
  vcpkg
  PATHS ${vcpkg_ROOT}
  )
  
find_file(vcpkg_CMAKE_TOOLCHAIN_FILE
  vcpkg.cmake
  PATHS
    "${vcpkg_ROOT}/scripts/buildsystems"
  )

#message(STATUS "VCPKG_ROOT = ${VCPKG_ROOT}")
#message(STATUS "vcpkg_ROOT = ${vcpkg_ROOT}")
#message(STATUS "vcpkg_EXECUTABLE = ${vcpkg_EXECUTABLE}")
#message(STATUS "vcpkg_CMAKE_TOOLCHAIN_FILE = ${vcpkg_CMAKE_TOOLCHAIN_FILE}")

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(vcpkg vcpkg_EXECUTABLE vcpkg_CMAKE_TOOLCHAIN_FILE)

if(vcpkg_FOUND AND
   NOT TARGET vcpkg::exe)
  add_executable(vcpkg::exe IMPORTED)
endif()

mark_as_advanced(vcpkg_EXECUTABLE)
