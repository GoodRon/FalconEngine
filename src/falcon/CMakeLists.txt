cmake_minimum_required(VERSION 3.1)

add_subdirectory(json)

add_library(falcon 
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
	UnitController.cxx
	IGameState.cxx
	Frame.cxx
	IEntity.cxx
	EntityManager.cxx
	ComponentRegistry.cxx
	SystemManager.cxx
	IEvent.cxx
	IComponent.cxx
	EventManager.cxx
	ISystem.cxx)

target_link_libraries(falcon SDL2::Core SDL2::Image)
