#include <iostream>
#include <algorithm>
#include <ctime>
#include <ratio>
#include <chrono>

#include "Matrix/Matrix.h"
#include "Utils/Utils.cpp"

using namespace LinearAlgebra;
using namespace Utils;
using namespace std::chrono;
using namespace std;


int main(){
    Matrix matrix1 = Matrix(3, 3, vector<int>{2, 3, -5, 6, 9, -7, 9, 4, 5});
    matrix1.print();
//    matrix1.slice(0, 1, 1, 2).print();
    (~matrix1).print();


//    Matrix<int> matrix2 = Matrix<int>(3, 2, {1, -2, 0, 3, 4, -5});
//
//    (matrix1 + -1000).print();


//    Matrix<int> matrix1 = Matrix<int>(10'000, 1000);
//    Matrix<int> matrix2 = Matrix<int>(10'000, 1000);
//
//    high_resolution_clock::time_point t11 = high_resolution_clock::now();
////    matrix1.smatrix(matrix2);
//
//    matrix1 + 999;
//
//    high_resolution_clock::time_point t12 = high_resolution_clock::now();
//    cout << "Matrix method: " << duration_cast<duration<double>>(t12 - t11).count() << endl;
//
//
//    high_resolution_clock::time_point t21 = high_resolution_clock::now();
//    matrix1.svector(999);
//    high_resolution_clock::time_point t22 = high_resolution_clock::now();
//    cout << "Vector method: " << duration_cast<duration<double>>(t22 - t21).count() << endl;


//    vector<int> vec = {2, 3, -5, 6, 9, -7};
//
//    auto i1 = apply_(vec, [](int a){return 2 * a;}, false);
//
//    for (auto i : i1)
//        cout << i << endl;

    return 0;
}

