SET(test_cl_glitcher_static_mods_sources
        test_cl_glitcher_static_mods_histogram_shift.cpp)

# Boilerplate to make file list absolute directories.
# Required for the the master test executable
list(TRANSFORM test_cl_glitcher_static_mods_sources PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/)

add_executable(test_cl_glitcher_static_mods
        ${test_cl_glitcher_static_mods_sources})
target_link_libraries(test_cl_glitcher_static_mods PUBLIC
        gtest gtest_main cl_glitcher_mod_histogram_shift)
#target_include_directories(test_cl_glitcher_static_mods_histogram_shift PUBLIC
#        ${CLI11_INCLUDE_DIR} ${CL_GLITCHER_INCLUDE_DIR})

