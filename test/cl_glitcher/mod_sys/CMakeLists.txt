SET(test_cl_glitcher_mod_sys_sources
        test_cl_glitcher_mod_sys.cpp)

# Boilerplate to make file list absolute directories.
# Required for the the master test executable
list(TRANSFORM test_cl_glitcher_mod_sys_sources PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/)

add_executable(test_cl_glitcher_mod_sys ${test_cl_glitcher_mod_sys_sources})
target_link_libraries(test_cl_glitcher_mod_sys PUBLIC gtest gtest_main cl_glitcher_mod_sys)
#target_include_directories(test_cl_glitcher_mod_sys PUBLIC
#        ${CLI11_INCLUDE_DIR} ${CL_GLITCHER_INCLUDE_DIR})

target_compile_definitions(test_cl_glitcher_mod_sys PUBLIC
        -DCL_GLITCHER_TEST_DIRECTORY_MOD_SYS="${CMAKE_CURRENT_SOURCE_DIR}")

add_subdirectory(dynamic_mod_lib_1)

add_dependencies(test_cl_glitcher_mod_sys test_cl_glitcher_mod_sys_dynamic_mod_lib_1)