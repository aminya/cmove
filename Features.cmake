# building the tests
option(FEATURE_TESTS "Enable the tests" OFF)
if(FEATURE_TESTS)
  list(APPEND VCPKG_MANIFEST_FEATURES "tests")
endif()

# building the docs
option(FEATURE_DOCS "Enable the docs" OFF)
