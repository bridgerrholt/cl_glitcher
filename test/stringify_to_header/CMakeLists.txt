#add_executable(pre_test_stringify_to_header pre_test_stringify_to_header.cpp)
#target_link_libraries(pre_test_stringify_to_header PUBLIC stringify_to_header)
cmd_stringify_to_header(test testString1 test_stringify_to_header_1.txt test_stringify_to_header_1.h)
#add_custom_target(pre_test_stringify_to_header DEPENDS test_stringify_to_header_1.h)


SET(test_stringify_to_header_sources
        test_stringify_to_header.cpp
        test_stringify_to_header_1.txt)

# Boilerplate to make file list absolute directories.
# Required for the the master test executable
list(TRANSFORM test_stringify_to_header_sources PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/)

add_executable(test_stringify_to_header ${test_stringify_to_header_sources})
target_link_libraries(test_stringify_to_header PUBLIC gtest gtest_main stringify_to_header)
target_compile_definitions(test_stringify_to_header PUBLIC
        -DCL_GLITCHER_TEST_DIRECTORY_STRINGIFY_TO_HEADER="${CMAKE_CURRENT_SOURCE_DIR}")
#add_dependencies(test_stringify_to_header pre_test_stringify_to_header)