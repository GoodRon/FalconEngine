cmake_minimum_required(VERSION 3.1)

add_library(engine 
	STATIC
	ObjectManager.cxx 
	Tile.cxx
	WorldObject.cxx 
	Engine.cxx 
	TimerPool.cxx
	ResourceManager.cxx 
	Renderer.cxx 
	Animation.cxx 
	DirectedAnimation.cxx 
	Target.cxx 
	Unit.cxx 
	UnitIdleState.cxx 
	UnitMovementState.cxx 
	UnitMoveCommand.cxx 
	UnitController.cxx)

target_link_libraries(engine ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY} ${jsoncpp_LIBRARY})# pthread)
