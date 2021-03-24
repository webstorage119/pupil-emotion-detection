cmake_minimum_required(VERSION 3.17)
project(pupil)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenCV REQUIRED)
add_executable(pupil main.cpp include/image.h src/image.cpp)

include_directories(./include ./src)
include_directories(${OpenCV_INCLUDE_DIRS})
target_link_libraries(pupil ${OpenCV_LIBS})
