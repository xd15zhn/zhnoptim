cmake_minimum_required(VERSION 3.12)
project(zhnoptim VERSION 1.0.7)
set(CMAKE_BUILD_TYPE release)
add_library(${CMAKE_PROJECT_NAME} STATIC zhnoptim.cpp opt_de.cpp opt_ps.cpp)
