SET(test_json_property_sources
        test_json_property.cpp)

# Boilerplate to make file list absolute directories.
# Required for the the master test executable
list(TRANSFORM test_json_property_sources PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/)

add_executable(test_json_property ${test_json_property_sources})
target_link_libraries(test_json_property PUBLIC gtest gtest_main)
target_include_directories(test_json_property PUBLIC
        ${JSON_UTIL_INCLUDE_DIR}
        ${RAPIDJSON_INCLUDE_DIR})