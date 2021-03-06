add_library(cl_glitcher_mod_fractal_hist STATIC fractal_hist.cpp)
target_include_directories(cl_glitcher_mod_fractal_hist PUBLIC
        ${CL_GLITCHER_INCLUDE_DIR}
        ${CL_GLITCHER_INCLUDE_DIR}/static_mods/fractal_hist)

target_link_libraries(cl_glitcher_mod_fractal_hist PUBLIC json_util)