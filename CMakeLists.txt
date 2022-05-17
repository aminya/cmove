cmake_minimum_required(VERSION 3.16)

# set a default CXX standard for the tools and targets that do not specify them.
# If commented, the latest supported standard for your compiler is automatically set.
# set(CMAKE_CXX_STANDARD 20)

# Add project_options v0.21.1
# https://github.com/aminya/project_options
# Change the version in the following URL to update the package (watch the releases of the repository for future updates)
include(FetchContent)
FetchContent_Declare(_project_options URL https://github.com/aminya/project_options/archive/refs/tags/v0.21.1.zip)
FetchContent_MakeAvailable(_project_options)
include(${_project_options_SOURCE_DIR}/Index.cmake)

# Define the features of the project
include("./Features.cmake")

# install vcpkg dependencies: - should be called before defining project()
run_vcpkg()

# Set the project name and language
project(
  cmove
  VERSION 1.0.1
  DESCRIPTION ""
  HOMEPAGE_URL "https://github.com/cpp-best-practices/cmove"
  LANGUAGES CXX C)

# enable sanitizers and clang-tidy if running the tests
set(ENABLE_CLANG_TIDY OFF)
set(ENABLE_CPPCHECK OFF)
set(ENABLE_SANITIZER_ADDRESS OFF)
set(ENABLE_SANITIZER_UNDEFINED_BEHAVIOR OFF)
set(ENABLE_COVERAGE OFF)
if(FEATURE_TESTS)
  set(ENABLE_COVERAGE "ENABLE_COVERAGE")
  set(ENABLE_CLANG_TIDY "ENABLE_CLANG_TIDY")
  set(ENABLE_CPPCHECK "ENABLE_CPPCHECK")

  string(FIND "$ENV{PATH}" "$ENV{VSINSTALLDIR}" index_of_vs_install_dir)
  if(NOT
     "${CMAKE_SYSTEM_NAME}"
     STREQUAL
     "Windows") # not windows
    set(ENABLE_SANITIZER_ADDRESS "ENABLE_SANITIZER_ADDRESS")
    set(ENABLE_SANITIZER_UNDEFINED_BEHAVIOR "ENABLE_SANITIZER_UNDEFINED_BEHAVIOR")
  elseif(MSVC AND "${index_of_vs_install_dir}" STREQUAL "-1") # windows MSVC and has run vcvarsall
    set(ENABLE_SANITIZER_ADDRESS "ENABLE_SANITIZER_ADDRESS")
  endif()
endif()

if(FEATURE_DOCS)
  set(ENABLE_DOXYGEN "ENABLE_DOXYGEN")
else()
  set(ENABLE_DOXYGEN OFF)
endif()

# Initialize project_options variable related to this project
# This overwrites `project_options` and sets `project_warnings`
# uncomment to enable the options. Some of them accept one or more inputs:
project_options(
  ENABLE_CACHE
  ${ENABLE_CPPCHECK}
  ${ENABLE_CLANG_TIDY}
  # ENABLE_INTERPROCEDURAL_OPTIMIZATION
  # ENABLE_NATIVE_OPTIMIZATION
  ${ENABLE_DOXYGEN}
  ${ENABLE_COVERAGE}
  ${ENABLE_SANITIZER_ADDRESS}
  ${ENABLE_SANITIZER_UNDEFINED_BEHAVIOR}
  # ENABLE_SANITIZER_LEAK
  # ENABLE_SANITIZER_THREAD
  # ENABLE_SANITIZER_MEMORY
  # ENABLE_PCH
  # PCH_HEADERS
  # WARNINGS_AS_ERRORS
  # ENABLE_INCLUDE_WHAT_YOU_USE
  # ENABLE_USER_LINKER
  # ENABLE_BUILD_WITH_TIME_TRACE
  # ENABLE_UNITY
)

add_subdirectory("./cmove")

# the variables set using CACHE STRING "" are passed to package_project

# Package the project
package_project(
  TARGETS
  cmove
  project_options
  project_warnings
  INTERFACE_DEPENDENCIES_CONFIGURED
  ${cmove_DEPENDENCIES_CONFIGURED}
  INTERFACE_INCLUDES
  ${cmove_INCLUDE_DIR})

# If MSVC is being used, and ASAN is enabled, we need to set the debugger environment
# so that it behaves well with MSVC's debugger, and we can run the target from visual studio
if(MSVC)
  get_all_targets(all_targets)
  set_target_properties(${all_targets} PROPERTIES VS_DEBUGGER_ENVIRONMENT "PATH=$(VC_ExecutablePath_x64);%PATH%")
endif()

set(CPACK_PACKAGE_FILE_NAME "${CMAKE_PROJECT_NAME}-${CMAKE_PROJECT_VERSION}")

include(CPack)
