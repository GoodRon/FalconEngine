cmake_minimum_required(VERSION 2.8)

add_library(game IsometricField.cxx)
target_link_libraries(game engine)
