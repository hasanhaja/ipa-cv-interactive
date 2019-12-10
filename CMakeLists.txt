cmake_minimum_required(VERSION 3.15)
project(opencv_interactive)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 17)

add_executable(opencv_interactive src/main.cpp)
target_link_libraries(opencv_interactive ${OpenCV_LIBS})