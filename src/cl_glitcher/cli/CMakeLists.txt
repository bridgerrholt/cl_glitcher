add_library(cl_glitcher_cli STATIC cli.cpp)
target_include_directories(cl_glitcher_cli PUBLIC
        ${CL_GLITCHER_INCLUDE_DIR}
        ${CLI11_INCLUDE_DIR})