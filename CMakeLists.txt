cmake_minimum_required(VERSION 3.15)
project(ipa_cv_interactive)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 17)

add_executable(ipa_cv_interactive src/main.cpp)
target_link_libraries(ipa_cv_interactive ${OpenCV_LIBS})