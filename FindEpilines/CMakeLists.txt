cmake_minimum_required(VERSION 3.6)
project(work3)

set( CMAKE_BUILD_TYPE "Debug" )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(OpenCV_DIR /opt/ros/kinetic/share/OpenCV-3.3.1-dev/)

find_package(OpenCV 3.3.1 REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(work3  epiline.cpp)
target_link_libraries( work3 ${OpenCV_LIBS})


