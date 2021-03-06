SET(test_file_util_sources
        test_load_file_to_string.cpp)

# Boilerplate to make file list absolute directories.
# Required for the the master test executable
list(TRANSFORM test_file_util_sources PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/)

add_executable(test_file_util ${test_file_util_sources})
target_link_libraries(test_file_util PUBLIC gtest gtest_main file_util)
target_include_directories(test_file_util PUBLIC
        ${ROOT_INCLUDE_DIR})
target_compile_definitions(test_file_util PUBLIC
        -DCL_GLITCHER_TEST_DIRECTORY_FILE_UTIL="${CMAKE_CURRENT_SOURCE_DIR}")
