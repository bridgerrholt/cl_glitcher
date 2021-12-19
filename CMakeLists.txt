cmake_minimum_required(VERSION 3.16)
project(CL_Glitcher VERSION 0.0.0.1)
set(CMAKE_CXX_STANDARD 17)

include(cmake/stringify_to_header.cmake)
include(cmake/generate_version_info.cmake)

### OpenCV ###
# D:/Bridger/Documents/Programming/_Libs/opencv-3.4.2/bin-msys2/install/x64/mingw/lib OR
# D:\Programs\msys64\mingw64\lib
set(OPENCV_LIB_DIR "" CACHE PATH "Directory of OpenCV library files")

# D:/Bridger/Documents/Programming/_Libs/opencv-3.4.2/bin-msys2/install/include OR
# D:\Programs\msys64\mingw64\include\opencv4
set(OPENCV_INCLUDE_DIR "" CACHE PATH "Directory of OpenCV header files")

set(OPENCV_DLL_DIR "" CACHE PATH "Directory of OpenCV DLL files")

set(USE_OPENCV_WORLD 0 CACHE PATH "Whether or not to use opencv_world")

if(USE_OPENCV_WORLD)
    message(opencv_world)
    # find_package(OpenCV PATHS ${OPENCV_LIB_DIR} NO_CMAKE_PATH NO_CMAKE_ENVIRONMENT_PATH NO_PACKAGE_ROOT_PATH)
    find_library(OPENCV_WORLD NAMES opencv_world454 PATHS ${OPENCV_LIB_DIR} ${OPENCV_DLL_DIR})
    find_library(OPENCV_WORLD_DEBUG NAMES opencv_world454d PATHS ${OPENCV_LIB_DIR} ${OPENCV_DLL_DIR})
    set(OPENCV_LIBS optimized ${OPENCV_WORLD} debug ${OPENCV_WORLD_DEBUG})
else()
    find_library(CORE_LIB NAMES opencv_core PATHS ${OPENCV_LIB_DIR})
    find_library(IMG_PROC_LIB NAMES opencv_imgproc PATHS ${OPENCV_LIB_DIR})
    find_library(HIGH_GUI_LIB NAMES opencv_highgui PATHS ${OPENCV_LIB_DIR})
    #find_library(VIDEO_LIB NAMES opencv_video PATHS ${OPENCV_DIR})
    find_library(IMAGE_CODECS_LIB NAMES opencv_imgcodecs PATHS ${OPENCV_LIB_DIR})
    set(OPENCV_LIBS ${CORE_LIB} ${IMG_PROC_LIB} ${HIGH_GUI_LIB} ${IMAGE_CODECS_LIB})
endif()

message(${OPENCV_LIBS})



### OpenCL ###
# D:\Programs\NVIDIA GPU Computing Toolkit\CUDA\v11.2\lib\x64
set(OPENCL_LIB_DIR "" CACHE PATH "Directory of OpenCL library files")

# D:\Programs\NVIDIA GPU Computing Toolkit\CUDA\v11.2\include
set(OPENCL_INCLUDE_DIR "" CACHE PATH "Directory of OpenCL header files")

find_library(OPENCL_LIB NAMES OpenCL PATHS ${OPENCL_LIB_DIR})



### CLI11 ###
# D:\Bridger\Documents\Programming\C++\_libs\CLI11\include
set(CLI11_INCLUDE_DIR "" CACHE PATH "Directory of CLI11 header files")



### googletest
add_subdirectory(vendor/googletest)
enable_testing()



### rapidjson
set(RAPIDJSON_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/vendor/rapidjson/include)



### dynalo
set(DYNALO_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/vendor/dynalo/include)


### CL_Glitcher ###
set(ROOT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(CL_GLITCHER_INCLUDE_DIR ${ROOT_INCLUDE_DIR}/cl_glitcher)
set(JSON_UTIL_INCLUDE_DIR ${ROOT_INCLUDE_DIR}/json_util)
add_executable(cl_glitcher_bin src/cl_glitcher/main.cpp)
target_include_directories(cl_glitcher_bin PUBLIC
        ${CL_GLITCHER_INCLUDE_DIR}
        ${ROOT_INCLUDE_DIR})
target_include_directories(cl_glitcher_bin SYSTEM PUBLIC
        BEFORE
        ${OPENCV_INCLUDE_DIR}
        ${OPENCL_INCLUDE_DIR}
        ${CLI11_INCLUDE_DIR})
target_link_libraries(cl_glitcher_bin PUBLIC
        ${OPENCV_LIBS}
        ${OPENCL_LIB}
        cl_glitcher_cli)
set_target_properties(cl_glitcher_bin
    PROPERTIES OUTPUT_NAME cl_glitcher) # Rename output binary to cl_glitcher
add_subdirectory(src/cl_glitcher)

if (CMAKE_BUILD_TYPE MATCHES Debug)
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    target_compile_options(cl_glitcher_bin PUBLIC -O3)
endif ()

# target_compile_options(cl_glitcher_bin PUBLIC -static)

cmd_generate_version_info(version_info version git_commit ${CL_GLITCHER_INCLUDE_DIR}/version_info/version_info.h cl_glitcher_bin)

### json_util ###
add_subdirectory(src/json_util)



### file_util ###
add_subdirectory(src/file_util)



### stringify_to_header ###
add_subdirectory(src/stringify_to_header)



### generate_version_info ###
add_subdirectory(src/generate_version_info)



### Test
if(NOT DEFINED CL_GLITCHER_NO_TEST)
    add_subdirectory(test)
endif()



### Graph generation
#if (NOT DEFINED CL_GLITCHER_NO_GRAPH)
#    message(${CMAKE_COMMAND})
#    message(${CMAKE_BINARY_DIR})
#    add_custom_target(cl_glitcher_graphviz ALL
#            COMMAND ${CMAKE_COMMAND} "--graphviz=graphviz/cl_glitcher_graphviz.dot" .
#            COMMAND dot -Tpng cl_glitcher_graphviz.dot -o cl_glitcher_graphviz.png
#            WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
#            )
#endif()
#if(DEFINED CL_GLITCHER_GRAPH)
#    set(GRAPHVIZ_GRAPH_NAME "cl_glitcher_graph")
    #set(GRAPHVIZ_CUSTOM_TARGETS TRUE)
#    set(GRAPHVIZ_EXECUTABLES FALSE)
#endif()