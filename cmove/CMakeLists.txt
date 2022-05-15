add_library(cmove INTERFACE)
target_link_libraries(cmove INTERFACE project_options project_warnings) # link project_options/warnings

# Includes
set(cmove_INCLUDE_DIR
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    CACHE STRING "")
target_include_directories(cmove INTERFACE "$<BUILD_INTERFACE:${cmove_INCLUDE_DIR}>"
                                           "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

if(FEATURE_TESTS)
  add_subdirectory("./test")
endif()
