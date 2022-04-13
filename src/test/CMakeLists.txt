cmake_minimum_required(VERSION 3.1)

list(APPEND CMAKE_C_FLAGS "-mwindows")
list(APPEND CMAKE_CXX_FLAGS "-mwindows")

#add_executable(basicTest WIN32 main.cxx)
#target_link_libraries(basicTest game)

#add_executable(fieldTest WIN32 FieldTest.cxx)
#target_link_libraries(fieldTest game)

#add_executable(animationTest WIN32 animationTest.cxx)
#target_link_libraries(animationTest game)

add_executable(directedAnimationTest WIN32 directedAnimationTest.cxx)
target_link_libraries(directedAnimationTest game)

#install(TARGETS basicTest RUNTIME DESTINATION .)
#install(TARGETS fieldTest RUNTIME DESTINATION .)
#install(TARGETS animationTest RUNTIME DESTINATION .)
install(TARGETS directedAnimationTest RUNTIME DESTINATION .)
