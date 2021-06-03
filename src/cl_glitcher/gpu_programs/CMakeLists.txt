#cmd_stringify_to_header_no_prefix(
#        clglitch::gpu_programs::histogram_program
#        histogramStr
#        ${CL_GLITCHER_COMPUTE_KERNELS_SRC_DIR}/gpu_programs/histogram.cl
#        ${CL_GLITCHER_COMPUTE_KERNELS_DIR}/gpu_programs/histogram.h)

add_custom_command(
        OUTPUT ${CL_GLITCHER_COMPUTE_KERNELS_DIR}/gpu_programs/histogram.h
        COMMAND $<TARGET_FILE:stringify_to_header_bin>
        ARGS clglitch::gpu_programs::histogram_program histogramStr ${CL_GLITCHER_COMPUTE_KERNELS_SRC_DIR}/gpu_programs/histogram.cl ${CL_GLITCHER_COMPUTE_KERNELS_DIR}/gpu_programs/histogram.h
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        DEPENDS stringify_to_header_bin ${CL_GLITCHER_COMPUTE_KERNELS_SRC_DIR}/gpu_programs/histogram.cl
)
set_property(SOURCE histogram_program.cpp APPEND PROPERTY OBJECT_DEPENDS ${CL_GLITCHER_COMPUTE_KERNELS_DIR}/gpu_programs/histogram.h)

add_library(cl_glitcher_gpu_programs STATIC
        histogram_program.cpp
        sort_histogram.cpp
        ${CL_GLITCHER_COMPUTE_KERNELS_SRC_DIR}/gpu_programs/histogram.cl
        ${CL_GLITCHER_COMPUTE_KERNELS_DIR}/gpu_programs/histogram.h)
#target_sources(cl_glitcher_gpu_programs PUBLIC)
target_include_directories(cl_glitcher_gpu_programs PUBLIC
        ${CL_GLITCHER_INCLUDE_DIR})
target_link_libraries(cl_glitcher_gpu_programs PUBLIC cl_glitcher_gpu_util)