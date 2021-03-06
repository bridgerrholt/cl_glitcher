add_library(cl_glitcher_gpu_util STATIC init.cpp build_program.cpp)
target_include_directories(cl_glitcher_gpu_util PUBLIC
        ${CL_GLITCHER_INCLUDE_DIR}
        ${CLI11_INCLUDE_DIR}
        ${OPENCL_INCLUDE_DIR})
target_link_libraries(cl_glitcher_gpu_util PUBLIC ${OPENCL_LIB} file_util)