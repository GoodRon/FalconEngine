cmake_minimum_required(VERSION 2.8)

add_library(game Field.cxx)
target_link_libraries(game engine)
