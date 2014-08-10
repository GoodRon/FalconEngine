cmake_minimum_required(VERSION 2.8)

add_executable(test main.cxx)
target_link_libraries(test game)

add_executable(fieldTest FieldTest.cxx)
target_link_libraries(fieldTest game)

install(TARGETS test RUNTIME DESTINATION .)
install(TARGETS fieldTest RUNTIME DESTINATION .)
