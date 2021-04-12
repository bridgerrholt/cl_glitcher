add_library(cl_glitcher_cmd_execution STATIC execute_cmd.cpp cmd_execution.cpp cmd_execution_params.cpp
        ${CL_GLITCHER_INCLUDE_DIR}/cmd_execution/system_environment.h system_environment.cpp)
target_include_directories(cl_glitcher_cmd_execution PUBLIC
        ${ROOT_INCLUDE_DIR}
        ${CL_GLITCHER_INCLUDE_DIR})
target_include_directories(cl_glitcher_cmd_execution SYSTEM PUBLIC
        ${OPENCL_INCLUDE_DIR})
target_link_libraries(
        cl_glitcher_cmd_execution PUBLIC
        json_util cl_glitcher_mod_environment cl_glitcher_mod_sys cl_glitcher_gpu_util cl_glitcher_static_mods)

# add_library(cl_glitcher_cmd_execution_interface INTERFACE)
#target_include_directories(cl_glitcher_cmd_execution PUBLIC
#        "$<TARGET_PROPERTY:cl_glitcher_mod_sys,INCLUDE_DIRECTORIES>")