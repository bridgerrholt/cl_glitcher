add_library(cl_glitcher_image_util STATIC
        load_image.cpp)
#target_sources(cl_glitcher_image_util PUBLIC)
target_include_directories(cl_glitcher_image_util PUBLIC
        ${CL_GLITCHER_INCLUDE_DIR}
        ${OPENCV_INCLUDE_DIR})
target_link_libraries(cl_glitcher_image_util PUBLIC
        ${CORE_LIB} ${IMG_PROC_LIB} ${HIGH_GUI_LIB} ${IMAGE_CODECS_LIB})