cmake_minimum_required(VERSION 3.25)
project(project)

set(CMAKE_CXX_STANDARD 17)

add_executable(project task1.cpp Equation.cpp Equation.h multEqsSolution.cpp multEqsSolution.h)
