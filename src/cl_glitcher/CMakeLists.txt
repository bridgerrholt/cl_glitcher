set(CL_GLITCHER_COMPUTE_KERNELS_DIR ${CL_GLITCHER_INCLUDE_DIR}/compute_kernels)

add_subdirectory(cli)
add_subdirectory(gpu_util)
add_subdirectory(image_util)
add_subdirectory(mod_sys)

# Static mods
add_subdirectory(static_mods/fractal_hist)