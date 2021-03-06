cmake_minimum_required(VERSION 3.16)
project(CL_Glitcher)

set(CMAKE_CXX_STANDARD 17)

include(cmake/stringify_to_header.cmake)

### OpenCV ###
# D:/Bridger/Documents/Programming/_Libs/opencv-3.4.2/bin-msys2/install/x64/mingw/lib OR
# D:\Programs\msys64\mingw64\lib
set(OPENCV_LIB_DIR "" CACHE PATH "Directory of OpenCV library files")

# D:/Bridger/Documents/Programming/_Libs/opencv-3.4.2/bin-msys2/install/include OR
# D:\Programs\msys64\mingw64\include\opencv4\opencv2
set(OPENCV_INCLUDE_DIR "" CACHE PATH "Directory of OpenCV header files")

find_library(CORE_LIB NAMES opencv_core PATHS ${OPENCV_LIB_DIR})
find_library(IMG_PROC_LIB NAMES opencv_imgproc PATHS ${OPENCV_LIB_DIR})
find_library(HIGH_GUI_LIB NAMES opencv_highgui PATHS ${OPENCV_LIB_DIR})
#find_library(VIDEO_LIB NAMES opencv_video PATHS ${OPENCV_DIR})
find_library(IMAGE_CODECS_LIB NAMES opencv_imgcodecs PATHS ${OPENCV_LIB_DIR})



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
add_executable(cl_glitcher_bin src/cl_glitcher/main.cpp src/cl_glitcher/cli/cli.cpp include/cl_glitcher/cli/cli.h test/cl_glitcher/cli/test_cl_glitcher_cli.cpp)
target_include_directories(cl_glitcher_bin PUBLIC
    ${CL_GLITCHER_INCLUDE_DIR}
    ${OPENCV_INCLUDE_DIR}
    ${OPENCL_INCLUDE_DIR}
    ${CLI11_INCLUDE_DIR})
target_link_libraries(cl_glitcher_bin PUBLIC
    ${CORE_LIB} ${IMG_PROC_LIB} ${HIGH_GUI_LIB} ${IMAGE_CODECS_LIB}
    ${OPENCL_LIB})
set_target_properties(cl_glitcher_bin
    PROPERTIES OUTPUT_NAME cl_glitcher) # Rename output binary to cl_glitcher
add_subdirectory(src/cl_glitcher)



### json_util ###
add_subdirectory(src/json_util)



### file_util ###
add_subdirectory(src/file_util)



### stringify_to_header ###
add_subdirectory(src/stringify_to_header)



### Test
add_subdirectory(test)
