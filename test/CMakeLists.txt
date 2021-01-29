set(CL_GLITCHER_TEST_ROOT_DIR ${})

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_subdirectory(cl_glitcher)
add_subdirectory(json_util)


get_target_property(test_cl_glitcher_sources test_cl_glitcher SOURCES)
get_target_property(test_cl_glitcher_libs test_cl_glitcher LINK_LIBRARIES)

get_target_property(test_json_util_sources test_json_util SOURCES)
get_target_property(test_json_util_libs test_json_util LINK_LIBRARIES)

add_executable(test_all ${test_cl_glitcher_sources} ${test_json_util_sources})
target_link_libraries(test_all PUBLIC ${test_cl_glitcher_libs} ${test_json_util_libs})