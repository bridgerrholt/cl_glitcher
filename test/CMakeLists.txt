set(CL_GLITCHER_TEST_ROOT_DIR ${})
add_definitions(-DCL_GLITCHER_TEST_DIRECTORY="${CMAKE_CURRENT_SOURCE_DIR}")

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_subdirectory(cl_glitcher)
add_subdirectory(file_util)
add_subdirectory(json_util)
add_subdirectory(stringify_to_header)


get_target_property(test_cl_glitcher_sources test_cl_glitcher SOURCES)
get_target_property(test_cl_glitcher_libs test_cl_glitcher LINK_LIBRARIES)

get_target_property(test_json_util_sources test_json_util SOURCES)
get_target_property(test_json_util_libs test_json_util LINK_LIBRARIES)

add_executable(test_all ${test_cl_glitcher_sources} ${test_json_util_sources})
target_link_libraries(test_all PUBLIC ${test_cl_glitcher_libs} ${test_json_util_libs})
#add_dependencies(test_all pre_test_stringify_to_header)