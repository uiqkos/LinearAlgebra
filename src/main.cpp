#include <iostream>
#include <algorithm>
#include <ctime>
#include <ratio>
#include <chrono>

#include "Matrix/Matrix.cpp"
#include "Utils/Utils.cpp"

using namespace LinearAlgebra;
using namespace std;
using namespace std::chrono;


int main(){
    Matrix<int> matrix1 = Matrix<int>(3, 2, {2, 3, -5, 6, 9, -7});
    Matrix<int> matrix2 = Matrix<int>(2, 3, {1, -2, 0, 3, 4, -5});

    (matrix1 + -1000).print();


//    Matrix<int> matrix1 = Matrix<int>(10'000, 10'000);
//
//    high_resolution_clock::time_point t11 = high_resolution_clock::now();
//    matrix1.smatrix(999);
//    high_resolution_clock::time_point t12 = high_resolution_clock::now();
//    cout << "Matrix method: " << duration_cast<duration<double>>(t12 - t11).count() << endl;
//
//    high_resolution_clock::time_point t21 = high_resolution_clock::now();
//    matrix1.svector(999);
//
//    high_resolution_clock::time_point t22 = high_resolution_clock::now();
//    cout << "Vector method: " << duration_cast<duration<double>>(t22 - t21).count() << endl;


    return 0;
}

