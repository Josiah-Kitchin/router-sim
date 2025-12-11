cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_STANDARD 23)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
    add_definitions(-DDEBUG_BUILD)
endif()

project(router_sim CXX)

file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(sim ${SOURCES})

#source 
include_directories(./include ./libs)



