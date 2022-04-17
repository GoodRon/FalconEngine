cmake_minimum_required(VERSION 3.1)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(spacewars WIN32 
	main.cpp 
	GameBuilder.cpp
	EntityBuilder.cpp)
target_link_libraries(spacewars falcon SDL2::Main)

install(TARGETS spacewars RUNTIME DESTINATION .)
