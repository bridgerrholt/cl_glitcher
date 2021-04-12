add_library(cl_glitcher_gpu_util STATIC init.cpp build_program.cpp buffer_wrapper.cpp)
target_include_directories(cl_glitcher_gpu_util PUBLIC
        ${CL_GLITCHER_INCLUDE_DIR}
        ${OPENCL_INCLUDE_DIR})
target_link_libraries(cl_glitcher_gpu_util PUBLIC ${OPENCL_LIB} file_util)

get_target_property(LIBA_INCLUDES cl_glitcher_gpu_util INCLUDE_DIRECTORIES)
get_target_property(LIBA_LIBRARIES cl_glitcher_gpu_util LINK_LIBRARIES)
message(${LIBA_INCLUDES})
message(${LIBA_LIBRARIES})
message(cl_glitcher_gpu_util done)