cmake_minimum_required(VERSION 3.1)

add_subdirectory(json)

add_library(falcon 
	STATIC
	ObjectManager.cxx 
	Engine.cxx 
	TimerPool.cxx
	ResourceManager.cxx 
	Renderer.cxx 
	Frame.cxx
	Entity.cxx
	ComponentRegistry.cxx
	SystemManager.cxx
	IEvent.cxx
	IComponent.cxx
	EventManager.cxx
	ISystem.cxx
	IGameObject.cxx)

target_link_libraries(falcon SDL2::Core SDL2::Image)
