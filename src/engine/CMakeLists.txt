cmake_minimum_required(VERSION 2.8)

add_library(engine Engine.cxx TimerPool.cxx)
target_link_libraries(engine SDL2)
