
str_stringify_to_header(cmd_line
        clglitch::mandelbrot_shift::mandelbrot_shift_program
        mandelbrotShiftStr
        ${CL_GLITCHER_COMPUTE_KERNELS_SRC_DIR}/static_mods/mandelbrot_shift.cl
        ${CL_GLITCHER_COMPUTE_KERNELS_DIR}/static_mods/mandelbrot_shift.h)
add_custom_command(
        OUTPUT ${CL_GLITCHER_COMPUTE_KERNELS_DIR}/static_mods/mandelbrot_shift.h
        ${cmd_line}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        DEPENDS stringify_to_header_bin ${CL_GLITCHER_COMPUTE_KERNELS_SRC_DIR}/static_mods/mandelbrot_shift.cl
)


add_library(cl_glitcher_mod_mandelbrot_shift STATIC mandelbrot_shift.cpp
        ${CL_GLITCHER_COMPUTE_KERNELS_SRC_DIR}/static_mods/mandelbrot_shift.cl
        ${CL_GLITCHER_COMPUTE_KERNELS_DIR}/static_mods/mandelbrot_shift.h mandelbrot_shift_program.cpp)
target_include_directories(cl_glitcher_mod_mandelbrot_shift PUBLIC
        ${ROOT_INCLUDE_DIR}
        ${CL_GLITCHER_INCLUDE_DIR}
        ${CL_GLITCHER_INCLUDE_DIR}/static_mods/mandelbrot_shift)

target_link_libraries(cl_glitcher_mod_mandelbrot_shift PUBLIC
        cl_glitcher_gpu_util
        json_util
        cl_glitcher_image_util
        cl_glitcher_gpu_programs
        cl_glitcher_mod_environment
        cl_glitcher_cmd_execution)