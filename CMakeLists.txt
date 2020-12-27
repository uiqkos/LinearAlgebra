cmake_minimum_required(VERSION 3.17)
project(LinearAlgebra)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS 1)
set(CMAKE_CXX_STANDARD 20)


add_library(
    LinearAlgebra SHARED
    src/Matrix/Matrix.cpp src/Matrix/Matrix.h
    src/Matrix/Slice/Slice.cpp src/Matrix/Slice/Slice.h
)

target_include_directories(LinearAlgebra PRIVATE src)

include_directories(src)

add_executable(
        LinearAlgebra_test src/main.cpp
        src/Matrix/Matrix.cpp src/Matrix/Matrix.h
        src/Matrix/Slice/Slice.cpp src/Matrix/Slice/Slice.h
)

target_link_libraries(LinearAlgebra_test LinearAlgebra)