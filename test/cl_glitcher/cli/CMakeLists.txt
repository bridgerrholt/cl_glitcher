SET(test_cl_glitcher_cli_sources
        test_cl_glitcher_cli.cpp
        test_cl_glitcher_cli_result.cpp)

# Boilerplate to make file list absolute directories.
# Required for the the master test executable
list(TRANSFORM test_cl_glitcher_cli_sources PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/)

add_executable(test_cl_glitcher_cli ${test_cl_glitcher_cli_sources})
target_link_libraries(test_cl_glitcher_cli PUBLIC gtest gtest_main cl_glitcher_cli)
target_include_directories(test_cl_glitcher_cli PUBLIC
        ${CLI11_INCLUDE_DIR} ${CL_GLITCHER_INCLUDE_DIR})