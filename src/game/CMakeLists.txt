cmake_minimum_required(VERSION 3.1)

add_library(game STATIC IsometricField.cxx)
target_link_libraries(game engine)
