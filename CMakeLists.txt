cmake_minimum_required(VERSION 3.0)
project(HPCSE2_ex2)
find_package(HPX REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fopenmp")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")
set(CMAKE_CXX_FLAGS_RELEASE  "-O3")

add_definitions(-DNUM_THREADS=4)

add_hpx_component(
        extend
        SOURCES src/extent.cpp
        HEADERS include/extend.h
)

add_hpx_component(
        sort
        SOURCES src/sort.cpp
        HEADERS include/sort.h
)

add_hpx_executable(
        ex2_hpx
        SOURCES main.cpp
        COMPONENT_DEPENDENCIES extend sort
)
