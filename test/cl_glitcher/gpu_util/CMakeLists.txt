SET(test_cl_glitcher_gpu_util_sources
        test_cl_glitcher_gpu_util.cpp
        test_cl_glitcher_vector_addition.h)

cmd_stringify_to_header(test vectorAdditionStr test_cl_glitcher_vector_addition.cl test_cl_glitcher_vector_addition.h)
add_executable(test_cl_glitcher_gpu_util ${test_cl_glitcher_gpu_util_sources})
target_link_libraries(test_cl_glitcher_gpu_util PUBLIC gtest gtest_main cl_glitcher_gpu_util)
target_include_directories(test_cl_glitcher_gpu_util PUBLIC
        ${CLI11_INCLUDE_DIR} ${CL_GLITCHER_INCLUDE_DIR})
target_compile_definitions(test_cl_glitcher_gpu_util PUBLIC
        -DCL_GLITCHER_TEST_DIRECTORY_GPU_UTIL="${CMAKE_CURRENT_SOURCE_DIR}")

#add_custom_target(pre_test_cl_glitcher_gpu_util DEPENDS test_cl_glitcher_vector_addition.h)
#add_dependencies(test_cl_glitcher_gpu_util pre_test_cl_glitcher_gpu_util)

# Boilerplate to make file list absolute directories.
# Required for the the master test executable
list(TRANSFORM test_cl_glitcher_gpu_util_sources PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/)