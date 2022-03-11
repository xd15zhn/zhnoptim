cmake_minimum_required(VERSION 3.12)
project(algorithm)
set(CMAKE_BUILD_TYPE release)
add_library(${CMAKE_PROJECT_NAME} STATIC opt_de.cpp opt_ps.cpp)
