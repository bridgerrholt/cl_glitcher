add_library(cl_glitcher_mod_sys STATIC load_dynamic_mods.cpp)
target_include_directories(cl_glitcher_mod_sys PUBLIC
        ${CL_GLITCHER_INCLUDE_DIR}
        ${DYNALO_INCLUDE_DIR})
target_link_libraries(cl_glitcher_mod_sys PUBLIC json_util)