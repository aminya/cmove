# Add a file containing a set of constexpr tests
add_executable(cmove_constexpr_tests "./constexpr_tests.cpp")

target_link_libraries(
  cmove_constexpr_tests
  PRIVATE cmove
          project_warnings
          project_options
          Catch2::Catch2
          fmt::fmt)
target_compile_definitions(cmove_constexpr_tests PRIVATE CATCH_CONFIG_MAIN)

catch_discover_tests(cmove_constexpr_tests ${COVERAGE_ARGS})

# Disable the constexpr portion of the test, and build again this allows us to have an executable that we can debug when
# things go wrong with the constexpr testing
add_executable(cmove_relaxed_constexpr_tests "./constexpr_tests.cpp")

target_link_libraries(
  cmove_relaxed_constexpr_tests
  PRIVATE cmove
          project_warnings
          project_options
          Catch2::Catch2
          fmt::fmt)
target_compile_definitions(cmove_relaxed_constexpr_tests PRIVATE CATCH_CONFIG_MAIN)
target_compile_definitions(cmove_relaxed_constexpr_tests PRIVATE -DCATCH_CONFIG_RUNTIME_STATIC_REQUIRE)

catch_discover_tests(cmove_relaxed_constexpr_tests ${COVERAGE_ARGS})
