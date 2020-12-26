cmake_minimum_required(VERSION 3.17)
project(LinearAlgebra)

set(CMAKE_CXX_STANDARD 20)

add_library(LinearAlgebra src/library.cpp src/library.h)
add_executable(LinearAlgebra_test src/main.cpp)
