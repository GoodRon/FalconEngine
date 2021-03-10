cmake_minimum_required(VERSION 2.8)

add_executable(basicTest main.cxx)
target_link_libraries(basicTest game)

add_executable(fieldTest FieldTest.cxx)
target_link_libraries(fieldTest game)

add_executable(animationTest animationTest.cxx)
target_link_libraries(animationTest game)

add_executable(directedAnimationTest directedAnimationTest.cxx)
target_link_libraries(directedAnimationTest game)

install(TARGETS basicTest RUNTIME DESTINATION .)
install(TARGETS fieldTest RUNTIME DESTINATION .)
install(TARGETS animationTest RUNTIME DESTINATION .)
install(TARGETS directedAnimationTest RUNTIME DESTINATION .)
