SET(test_json_util_sources
        test_json_property.cpp
        test_load_json_file.cpp)

# Boilerplate to make file list absolute directories.
# Required for the the master test executable
list(TRANSFORM test_json_util_sources PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/)

add_executable(test_json_util ${test_json_util_sources})
target_link_libraries(test_json_util PUBLIC gtest gtest_main)
target_include_directories(test_json_util PUBLIC
        ${JSON_UTIL_INCLUDE_DIR}
        ${RAPIDJSON_INCLUDE_DIR})

target_compile_definitions(test_json_util PUBLIC
        -DCL_GLITCHER_TEST_DIRECTORY_JSON_UTIL="${CMAKE_CURRENT_SOURCE_DIR}")