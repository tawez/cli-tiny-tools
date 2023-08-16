cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

project(serial-ports LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(serial-ports serial-ports.cpp)
