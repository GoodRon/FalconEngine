cmake_minimum_required(VERSION 3.1)

add_executable(basicTest WIN32 main.cxx)
target_link_libraries(basicTest game SDL2::Main)

add_executable(fieldTest WIN32 FieldTest.cxx)
target_link_libraries(fieldTest game SDL2::Main)

add_executable(animationTest WIN32 animationTest.cxx)
target_link_libraries(animationTest game SDL2::Main)

add_executable(directedAnimationTest WIN32 directedAnimationTest.cxx)
target_link_libraries(directedAnimationTest game SDL2::Main)

install(TARGETS basicTest RUNTIME DESTINATION .)
install(TARGETS fieldTest RUNTIME DESTINATION .)
install(TARGETS animationTest RUNTIME DESTINATION .)
install(TARGETS directedAnimationTest RUNTIME DESTINATION .)
