cmake_minimum_required(VERSION 2.8)

project(histogram)
set( CMAKE_CXX_FLAGS "-std=c++11" )

add_executable(${PROJECT_NAME} "../src/main.cpp" "../../histomgram/src/histogram.cpp" "../../basic/src/basic.cpp")

message(${PROJECT_SOURCE_DIR})
set(PROJECT_INIT_PATH "/home/sxy/Github/opencv_cpp")

set(Opencv_INCLUDE_DIRS "${PROJECT_INIT_PATH}/start/lib/opencv-3.4.1/include")
set(Opencv_LIBRARIES_DIRS "${PROJECT_INIT_PATH}/start/lib/opencv-3.4.1/lib64")

set(Opencv_LIBs
    "${PROJECT_INIT_PATH}/start/lib/opencv-3.4.1/lib64/libopencv_highgui.so"
    "${PROJECT_INIT_PATH}/start/lib/opencv-3.4.1/lib64/libopencv_imgproc.so"
    "${PROJECT_INIT_PATH}/start/lib/opencv-3.4.1/lib64/libopencv_imgcodecs.so"
    "${PROJECT_INIT_PATH}/start/lib/opencv-3.4.1/lib64/libopencv_core.so"
    "${PROJECT_INIT_PATH}/start/lib/opencv-3.4.1/lib64/libopencv_video.so"
    "${PROJECT_INIT_PATH}/start/lib/opencv-3.4.1/lib64/libopencv_videostab.so"
    "${PROJECT_INIT_PATH}/start/lib/opencv-3.4.1/lib64/libopencv_videoio.so"
    )
message(${Opencv_LIBRARIES_DIRS})
include_directories(${Opencv_INCLUDE_DIRS})
link_directories(${Opencv_LIBRARIES_DIRS})
target_link_libraries( histogram "${Opencv_LIBs}")
