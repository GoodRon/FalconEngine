cmake_minimum_required(VERSION 2.8)

add_library(engine Engine.cxx TimerPool.cxx ResourceManager.cxx)
target_link_libraries(engine SDL2 SDL2_image)
