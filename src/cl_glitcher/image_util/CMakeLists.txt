add_library(cl_glitcher_image_util STATIC histogram_program.cpp)
target_include_directories(cl_glitcher_image_util PUBLIC
        ${CL_GLITCHER_INCLUDE_DIR}
        ${DYNALO_INCLUDE_DIR})
target_link_libraries(cl_glitcher_image_util PUBLIC json_util)
target_sources(cl_glitcher_image_util PUBLIC ${CL_GLITCHER_COMPUTE_KERNELS_DIR})