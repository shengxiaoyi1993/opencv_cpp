cmake_minimum_required(VERSION 2.8)

project(example)
set( CMAKE_CXX_FLAGS "-std=c++11" )

add_executable(${PROJECT_NAME} "../src/main.cpp" "../../basic/src/basic.cpp")

message(${PROJECT_SOURCE_DIR})
string(REGEX REPLACE "(.+)\\learn/exampleform.*" "\\1" PROJECT_INIT_PATH ${PROJECT_SOURCE_DIR})


set(Opencv_INCLUDE_DIRS "${PROJECT_INIT_PATH}/start/lib/opencv-3.4.1/include")
set(Opencv_LIBRARIES_DIRS "${PROJECT_INIT_PATH}/start/lib/opencv-3.4.1/lib64")

FILE(GLOB_RECURSE Opencv_LIBs "${PROJECT_INIT_PATH}start/lib/opencv-3.4.1/lib64/*.so")


message(${Opencv_LIBRARIES_DIRS})
include_directories(${Opencv_INCLUDE_DIRS})
link_directories(${Opencv_LIBRARIES_DIRS})
target_link_libraries( example "${Opencv_LIBs}")
