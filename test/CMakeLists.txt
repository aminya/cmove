# test dependencies
set(tests_DEPENDENCIES_CONFIGURED Catch2 fmt)

foreach(DEPENDENCY ${tests_DEPENDENCIES_CONFIGURED})
  find_package(${DEPENDENCY} CONFIG REQUIRED)
endforeach()

include(CTest)
include(Catch)

# test executable

add_executable(cmove_tests "./tests.cpp")

target_link_libraries(
  cmove_tests
  PRIVATE cmove
          project_warnings
          project_options
          Catch2::Catch2
          fmt::fmt)
# generate a main function for the test executable
target_compile_definitions(cmove_tests PRIVATE CATCH_CONFIG_MAIN)

# use xml reporter if coverage is enabled
if(${ENABLE_COVERAGE})
  set(COVERAGE_ARGS REPORTER xml)
endif()

# automatically discover tests that are defined in catch based test files you can modify the tests
catch_discover_tests(cmove_tests ${COVERAGE_ARGS})

# constexpr tests
add_subdirectory("./constexpr")

# set the startup project for the "play" button in MSVC
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT cmove_tests)
