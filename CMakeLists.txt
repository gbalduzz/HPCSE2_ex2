cmake_minimum_required(VERSION 3.0)
project(HPCSE2_ex2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(ex2 ${SOURCE_FILES})