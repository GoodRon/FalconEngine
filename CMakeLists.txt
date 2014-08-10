project(FalconEngine)
cmake_minimum_required(VERSION 2.8)

add_definitions(-Wall -Wextra)
add_definitions(-D_REENTRANT)
add_definitions(-std=c++0x)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/engine)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/game)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/engine)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/game)

add_subdirectory(src)
