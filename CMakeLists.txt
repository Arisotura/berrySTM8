cmake_minimum_required(VERSION 3.27)
project(berrySTM8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(berrySTM8
        src/main.cpp
        src/STM8.cpp)

target_link_libraries(berrySTM8 ${SDL2_LIBRARIES})
