cmake_minimum_required(VERSION 3.19)
project(Ai)
set(CMAKE_CXX_STANDARD 14)
# includes cmake/FindSDL2.cmake
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

set(SOURCE_FILES src/main.cpp)

add_executable(Ai main.cpp)
target_link_libraries(Ai ${SDL2_LIBRARY})