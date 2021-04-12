set(CL_GLITCHER_COMPUTE_KERNELS_DIR ${CL_GLITCHER_INCLUDE_DIR}/compute_kernels)
set(CL_GLITCHER_COMPUTE_KERNELS_SRC_DIR ${CL_GLITCHER_COMPUTE_KERNELS_DIR}/opencl)

add_subdirectory(cli)
add_subdirectory(gpu_util)
add_subdirectory(gpu_programs)
add_subdirectory(image_util)
add_subdirectory(mod_environment)
add_subdirectory(mod_sys)
add_subdirectory(cmd_execution)

# Static mods
add_subdirectory(static_mods)