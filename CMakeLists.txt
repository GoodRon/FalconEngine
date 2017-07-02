project(FalconEngine)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

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

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})

find_package(SDL2_image REQUIRED)
include_directories(${SDL2_IMAGE_INCLUDE_DIR})

find_package(Jsoncpp REQUIRED)
include_directories(${JSONCPP_INCLUDE_DIR})

add_definitions(-Wall -Wextra)
add_definitions(-D_REENTRANT)
add_definitions(-std=c++0x)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/engine)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/game)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/engine)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/game)

add_subdirectory(src)
add_subdirectory(data)
