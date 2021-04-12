SET(test_cl_glitcher_cmd_execution_sources
        test_cl_glitcher_cmd_execution.cpp)

# Boilerplate to make file list absolute directories.
# Required for the the master test executable
list(TRANSFORM test_cl_glitcher_cmd_execution_sources PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/)

add_executable(test_cl_glitcher_cmd_execution ${test_cl_glitcher_cmd_execution_sources})
target_link_libraries(test_cl_glitcher_cmd_execution PUBLIC gtest gtest_main cl_glitcher_cmd_execution)
target_include_directories(test_cl_glitcher_cmd_execution PUBLIC
        ${cmd_execution11_INCLUDE_DIR} ${CL_GLITCHER_INCLUDE_DIR})

target_compile_definitions(test_cl_glitcher_cmd_execution PUBLIC
        -DCL_GLITCHER_TEST_DIRECTORY_CMD_EXECUTION="${CMAKE_CURRENT_SOURCE_DIR}")
