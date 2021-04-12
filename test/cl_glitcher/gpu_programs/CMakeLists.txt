SET(test_cl_glitcher_gpu_programs_sources
        test_cl_glitcher_gpu_programs.cpp)

# Boilerplate to make file list absolute directories.
# Required for the the master test executable
list(TRANSFORM test_cl_glitcher_gpu_programs_sources PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/)

add_executable(test_cl_glitcher_gpu_programs ${test_cl_glitcher_gpu_programs_sources})
target_link_libraries(test_cl_glitcher_gpu_programs PUBLIC gtest gtest_main cl_glitcher_gpu_programs)
#target_compile_definitions(test_cl_glitcher_gpu_programs PUBLIC
#        -DCL_GLITCHER_TEST_DIRECTORY_gpu_programs="${CMAKE_CURRENT_SOURCE_DIR}")
