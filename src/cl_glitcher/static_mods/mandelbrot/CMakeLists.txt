
str_stringify_to_header(cmd_line
        clglitch::mandelbrot::mandelbrot_program
        mandelbrotStr
        ${CL_GLITCHER_COMPUTE_KERNELS_SRC_DIR}/static_mods/mandelbrot.cl
        ${CL_GLITCHER_COMPUTE_KERNELS_DIR}/static_mods/mandelbrot.h)
add_custom_command(
        OUTPUT ${CL_GLITCHER_COMPUTE_KERNELS_DIR}/static_mods/mandelbrot.h
        ${cmd_line}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        DEPENDS stringify_to_header_bin ${CL_GLITCHER_COMPUTE_KERNELS_SRC_DIR}/static_mods/mandelbrot.cl
)


add_library(cl_glitcher_mod_mandelbrot STATIC mandelbrot.cpp
        ${CL_GLITCHER_COMPUTE_KERNELS_SRC_DIR}/static_mods/mandelbrot.cl
        ${CL_GLITCHER_COMPUTE_KERNELS_DIR}/static_mods/mandelbrot.h mandelbrot_program.cpp)
target_include_directories(cl_glitcher_mod_mandelbrot PUBLIC
        ${ROOT_INCLUDE_DIR}
        ${CL_GLITCHER_INCLUDE_DIR}
        ${CL_GLITCHER_INCLUDE_DIR}/static_mods/mandelbrot)

target_link_libraries(cl_glitcher_mod_mandelbrot PUBLIC
        cl_glitcher_gpu_util
        json_util
        cl_glitcher_image_util
        cl_glitcher_gpu_programs
        cl_glitcher_mod_environment
        cl_glitcher_cmd_execution)