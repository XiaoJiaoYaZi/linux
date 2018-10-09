cmake_minimum_required(VERSION 2.8)

project(linux_6)

FILE(GLOB incs ./*.h*)
add_custom_target(includes SOURCES ${incs})

add_definitions(-std=c++11)
add_executable(${PROJECT_NAME} "main.cpp")
target_link_libraries(${PROJECT_NAME} curses)
