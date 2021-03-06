#cmd_stringify_to_header_no_prefix(
#        clglitch::image_util::histogram_program
#        histogramStr
#        ${CL_GLITCHER_COMPUTE_KERNELS_SRC_DIR}/image_util/histogram.cl
#        ${CL_GLITCHER_COMPUTE_KERNELS_DIR}/image_util/histogram.h)

str_stringify_to_header(cmd_line
        clglitch::image_util::histogram_program
        histogramStr
        ${CL_GLITCHER_COMPUTE_KERNELS_SRC_DIR}/image_util/histogram.cl
        ${CL_GLITCHER_COMPUTE_KERNELS_DIR}/image_util/histogram.h)
add_custom_command(
        OUTPUT ${CL_GLITCHER_COMPUTE_KERNELS_DIR}/image_util/histogram.h
        #COMMAND $<TARGET_FILE:stringify_to_header_bin> clglitch::image_util::histogram_program histogramStr ${CL_GLITCHER_COMPUTE_KERNELS_SRC_DIR}/image_util/histogram.cl ${CL_GLITCHER_COMPUTE_KERNELS_DIR}/image_util/histogram.h
        ${cmd_line}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        DEPENDS stringify_to_header_bin ${CL_GLITCHER_COMPUTE_KERNELS_SRC_DIR}/image_util/histogram.cl
)

add_library(cl_glitcher_image_util STATIC
        histogram_program.cpp
        ${CL_GLITCHER_COMPUTE_KERNELS_SRC_DIR}/image_util/histogram.cl
        ${CL_GLITCHER_COMPUTE_KERNELS_DIR}/image_util/histogram.h)
#target_sources(cl_glitcher_image_util PUBLIC)
target_include_directories(cl_glitcher_image_util PUBLIC
        ${CL_GLITCHER_INCLUDE_DIR}
        ${DYNALO_INCLUDE_DIR})
target_link_libraries(cl_glitcher_image_util PUBLIC cl_glitcher_gpu_util)