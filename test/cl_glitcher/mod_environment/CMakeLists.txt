SET(test_cl_glitcher_mod_environment_sources
        test_cl_glitcher_mod_environment.cpp)

# Boilerplate to make file list absolute directories.
# Required for the the master test executable
list(TRANSFORM test_cl_glitcher_mod_environment_sources PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/)

add_executable(test_cl_glitcher_mod_environment ${test_cl_glitcher_mod_environment_sources})
target_link_libraries(test_cl_glitcher_mod_environment PUBLIC gtest gtest_main cl_glitcher_mod_environment)
#target_include_directories(test_cl_glitcher_mod_environment PUBLIC
#        ${CLI11_INCLUDE_DIR} ${CL_GLITCHER_INCLUDE_DIR})

target_compile_definitions(test_cl_glitcher_mod_environment PUBLIC
        -DCL_GLITCHER_TEST_DIRECTORY_MOD_ENVIRONMENT="${CMAKE_CURRENT_SOURCE_DIR}")
