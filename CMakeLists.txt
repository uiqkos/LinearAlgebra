cmake_minimum_required(VERSION 3.17)
project(LinearAlgebra)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS 1)
set(CMAKE_CXX_STANDARD 20)


add_library(
    LinearAlgebra SHARED
    src/Matrix/Matrix.h
    src/Utils/Utils.cpp
    src/Index/Index.cpp src/Index/Index.h src/Slice/Slice.cpp src/Slice/Slice.h src/Fraction/Fraction.cpp src/Fraction/Fraction.h)

target_include_directories(LinearAlgebra PRIVATE src)

include_directories(src)

add_executable(
        LinearAlgebra_test
        src/main.cpp
        src/Matrix/Matrix.h
        src/Utils/Utils.cpp
        src/Index/Index.cpp src/Index/Index.h
        src/Slice/Slice.cpp src/Slice/Slice.h
        src/Fraction/Fraction.cpp src/Fraction/Fraction.h)

target_link_libraries(LinearAlgebra_test LinearAlgebra)