cmake_minimum_required(VERSION 2.8)

project(linux_5)
aux_source_directory(. DIR_SRCS)

FILE(GLOB incs ./*.h*)
FILE(GLOB srcs ./*.cpp)
add_custom_target(includes SOURCES ${incs})
add_custom_target(sources SOURCES ${srcs})

add_definitions(-std=c++11)
add_executable(${PROJECT_NAME} "main.cpp")
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./result/)
#add_executable(${PROJECT_NAME} ${DIR_SRCS})

