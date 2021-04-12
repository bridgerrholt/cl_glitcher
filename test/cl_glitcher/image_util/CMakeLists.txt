SET(test_cl_glitcher_image_util_sources
        test_cl_glitcher_image_util.cpp)

# Boilerplate to make file list absolute directories.
# Required for the the master test executable
list(TRANSFORM test_cl_glitcher_image_util_sources PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/)

add_executable(test_cl_glitcher_image_util ${test_cl_glitcher_image_util_sources})
target_link_libraries(test_cl_glitcher_image_util PUBLIC gtest gtest_main cl_glitcher_image_util)
#target_compile_definitions(test_cl_glitcher_image_util PUBLIC
#        -DCL_GLITCHER_TEST_DIRECTORY_image_util="${CMAKE_CURRENT_SOURCE_DIR}")

target_compile_definitions(test_cl_glitcher_image_util PUBLIC
        -DCL_GLITCHER_TEST_DIRECTORY_IMAGE_UTIL="${CMAKE_CURRENT_SOURCE_DIR}")