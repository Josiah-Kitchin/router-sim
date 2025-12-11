cmake_minimum_required(VERSION 3.10)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)

project(Testing CXX)


file(GLOB_RECURSE SOURCES "../src/*.cpp")
list(FILTER SOURCES EXCLUDE REGEX "main.cpp$")

file(GLOB TEST_SOURCES "*.cpp") 


set(GTEST_DIR ./googletest)  
add_subdirectory(${GTEST_DIR} gtest)

add_executable(test ${SOURCES} ${TEST_SOURCES})

include_directories(../include ../libs) 


target_link_libraries(test PRIVATE 
    gtest
    gtest_main
)

target_compile_options(test PRIVATE -Wall -Wextra -g) 

set(CMAKE_BUILD_TYPE Debug)




