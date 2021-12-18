SET(test_generate_version_info_sources
        test_generate_version_info.cpp
        test_generate_version_info_1.h)

cmd_generate_version_info(test version git_commit test_generate_version_info_1.h test_generate_version_info.cpp)

add_executable(test_generate_version_info ${test_generate_version_info_sources})
target_link_libraries(test_generate_version_info PUBLIC gtest gtest_main generate_version_info)
target_compile_definitions(test_generate_version_info PUBLIC
        -DCL_GLITCHER_TEST_DIRECTORY_GENERATE_VERSION_INFO="${CMAKE_CURRENT_SOURCE_DIR}")

# Boilerplate to make file list absolute directories.
# Required for the the master test executable
list(TRANSFORM test_generate_version_info_sources PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/)
