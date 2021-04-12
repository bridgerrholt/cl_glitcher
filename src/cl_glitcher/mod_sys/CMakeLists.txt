add_library(cl_glitcher_mod_sys STATIC load_dynamic_mods.cpp mod_sys.cpp load_static_mods.cpp)
target_include_directories(cl_glitcher_mod_sys PUBLIC
        ${ROOT_INCLUDE_DIR}
        ${CL_GLITCHER_INCLUDE_DIR})
target_include_directories(cl_glitcher_mod_sys SYSTEM PUBLIC
        ${DYNALO_INCLUDE_DIR}
        ${OPENCL_INCLUDE_DIR})
target_link_libraries(cl_glitcher_mod_sys PUBLIC ${OPENCL_LIB} cl_glitcher_gpu_util json_util cl_glitcher_mod_histogram_shift)

add_library(cl_glitcher_mod_sys_interface INTERFACE)
target_include_directories(cl_glitcher_mod_sys_interface INTERFACE
        "$<TARGET_PROPERTY:json_util,INCLUDE_DIRECTORIES>")

get_target_property(LIBA_INCLUDES cl_glitcher_mod_sys INCLUDE_DIRECTORIES)
get_target_property(LIBA_LIBRARIES cl_glitcher_mod_sys LINK_LIBRARIES)
message(${LIBA_INCLUDES})
message(${LIBA_LIBRARIES})
message(done)