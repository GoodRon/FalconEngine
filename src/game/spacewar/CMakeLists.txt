cmake_minimum_required(VERSION 3.1)

add_subdirectory(data)

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(spacewar WIN32 
	main.cxx
	GameBuilder.cxx
	EntityBuilder.cxx
	misc/Quadtree.cxx
	misc/VelocityHelpers.cxx
	systems/PlayerControlSystem.cxx
	systems/RespawnSystem.cxx
	systems/PositioningSystem.cxx
	systems/GravitationalSystem.cxx
	systems/StateSystem.cxx
	systems/CollisionSystem.cxx
	systems/LifetimeSystem.cxx
	systems/VelocitySystem.cxx)
target_link_libraries(spacewar firefly SDL2::Main)

install(TARGETS spacewar RUNTIME DESTINATION .)
