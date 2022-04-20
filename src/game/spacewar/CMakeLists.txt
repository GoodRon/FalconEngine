cmake_minimum_required(VERSION 3.1)

add_subdirectory(data)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(spacewars WIN32 
	main.cxx
	GameBuilder.cxx
	EntityBuilder.cxx
	systems/PlayerControlSystem.cxx
	systems/PositioningSystem.cxx
	systems/GravitationalSystem.cxx
	systems/ShipStateSystem.cxx)
target_link_libraries(spacewars firefly SDL2::Main)

install(TARGETS spacewars RUNTIME DESTINATION .)
