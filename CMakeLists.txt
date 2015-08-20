project(FalconEngine)
cmake_minimum_required(VERSION 2.8)

# doxygen staff
configure_file( Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile )
include(FindDoxygen)
if( DOXYGEN_FOUND )
	# для ручного запуска, CI делает через плагин
	add_custom_target(
		doc
		COMMENT "Doxygen documentation" DEPENDS
		${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
		COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
	)
endif()

add_definitions(-Wall -Wextra)
add_definitions(-D_REENTRANT)
add_definitions(-std=c++0x)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/engine)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/game)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/engine)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/game)

add_subdirectory(src)
add_subdirectory(data)
