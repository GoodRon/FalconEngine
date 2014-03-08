cmake_minimum_required(VERSION 2.8)

add_executable(test main.cpp)
target_link_libraries(test engine)

install(TARGETS test RUNTIME DESTINATION .)
