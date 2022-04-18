cmake_minimum_required(VERSION 3.1)

add_library(firefly 
	STATIC
	ObjectManager.cxx 
	Engine.cxx 
	TimerPool.cxx
	ResourceManager.cxx 
	Renderer.cxx 
	Frame.cxx
	Entity.cxx
	SystemManager.cxx
	EventManager.cxx
	GameObject.cxx
	events/IEvent.cxx
	components/IComponent.cxx
	systems/ISystem.cxx
	systems/RenderingSystem.cxx
	systems/PlayerControlSystem.cxx)

target_link_libraries(firefly SDL2::Core SDL2::Image)
