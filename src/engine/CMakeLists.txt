cmake_minimum_required(VERSION 2.8)

add_library(engine Tile.cxx ObjectManager.cxx WorldObject.cxx Engine.cxx TimerPool.cxx
ResourceManager.cxx Renderer.cxx Animation.cxx DirectedAnimation.cxx Target.cxx 
Unit.cxx UnitIdleState.cxx UnitMovementState.cxx UnitMoveCommand.cxx)
target_link_libraries(engine SDL2 SDL2_image jsoncpp)
