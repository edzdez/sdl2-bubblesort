cmake_minimum_required(VERSION 3.19)
project(SDL2_Test)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

set(SOURCE_FILES src/main.cpp src/RenderWindow.cpp include/RenderWindow.h)
add_executable(SDL2_Test ${SOURCE_FILES})
target_link_libraries(SDL2_Test ${SDL2_LIBRARIES})