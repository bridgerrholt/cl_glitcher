add_library(test_cl_glitcher_mod_sys_dynamic_mod_lib_1 SHARED dynamic_mod_lib_1.cpp)

target_include_directories(test_cl_glitcher_mod_sys_dynamic_mod_lib_1 PUBLIC
        ${CL_GLITCHER_INCLUDE_DIR}
        ${DYNALO_INCLUDE_DIR})

target_link_libraries(test_cl_glitcher_mod_sys_dynamic_mod_lib_1 cl_glitcher_mod_sys_interface)

get_target_property(test_includes_msg test_cl_glitcher_mod_sys_dynamic_mod_lib_1 INCLUDE_DIRECTORIES)
message(${test_includes_msg})

# Required for dynalo when using MinGW.
# This is because dynalo doesn't expect lib prefix on Windows.
IF (WIN32)
    IF (NOT MSVC)
        set_target_properties(
                test_cl_glitcher_mod_sys_dynamic_mod_lib_1
                PROPERTIES PREFIX  "")
    ENDIF()
ENDIF(WIN32)