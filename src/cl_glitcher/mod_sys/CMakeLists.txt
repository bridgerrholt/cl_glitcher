add_library(cl_glitcher_mod_sys STATIC load_dynamic_mods.cpp mod_sys.cpp load_static_mods.cpp)
target_include_directories(cl_glitcher_mod_sys PUBLIC
        ${CL_GLITCHER_INCLUDE_DIR}
        ${DYNALO_INCLUDE_DIR})
target_link_libraries(cl_glitcher_mod_sys PUBLIC json_util)

add_library(cl_glitcher_mod_sys_interface INTERFACE)
target_include_directories(cl_glitcher_mod_sys_interface INTERFACE
        "$<TARGET_PROPERTY:json_util,INCLUDE_DIRECTORIES>")