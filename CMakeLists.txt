cmake_minimum_required(VERSION 3.17)
project(linal)
set(CMAKE_CXX_STANDARD 11) # C++11...
set(CMAKE_CXX_STANDARD_REQUIRED ON) #...is required...
set(CMAKE_CXX_EXTENSIONS OFF) #...without compiler extensions like gnu++11

file(GLOB SOURCES "*.cpp")

add_executable(linal ${SOURCES})