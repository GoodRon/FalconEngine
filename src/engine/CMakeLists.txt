cmake_minimum_required(VERSION 2.8)

add_library(engine WorldObject.cxx Engine.cxx TimerPool.cxx ResourceManager.cxx Renderer.cxx)
target_link_libraries(engine SDL2 SDL2_image)
