cmake_minimum_required(VERSION 3.29)
project(Algorithms)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB COMMON_SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_subdirectory(Assignment1)
add_subdirectory(Assignment2)
add_subdirectory(Assignment3)
add_subdirectory(Assignment4)