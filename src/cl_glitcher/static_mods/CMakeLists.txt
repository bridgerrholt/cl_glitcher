add_subdirectory(histogram_shift)

add_library(cl_glitcher_static_mods INTERFACE)

target_link_libraries(cl_glitcher_mod_histogram_shift PUBLIC
        cl_glitcher_mod_histogram_shift)