add_subdirectory(histogram_shift)
add_subdirectory(mandelbrot_shift)
add_subdirectory(mandelbrot)

add_library(cl_glitcher_static_mods INTERFACE)

target_link_libraries(cl_glitcher_static_mods INTERFACE
        cl_glitcher_mod_histogram_shift)
target_link_libraries(cl_glitcher_static_mods INTERFACE
        cl_glitcher_mod_mandelbrot_shift)
target_link_libraries(cl_glitcher_static_mods INTERFACE
        cl_glitcher_mod_mandelbrot)