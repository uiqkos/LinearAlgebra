#include <iostream>
#include <algorithm>
#include <ctime>
#include <ratio>
#include <chrono>

#include "Matrix/Matrix.h"
//#include "Utils/Utils.cpp"

using namespace LinearAlgebra;
using namespace Utils;
using namespace std::chrono;
using namespace std;

int main(){
    Matrix matrix1 = Matrix(3, 3, vector<int>{2, 3, -5, 6, 9, -7, 9, 4, 5});
    Matrix matrix2 = Matrix(1, 3, vector<int>{-5, -7, 9});

    cout << matrix1[{1, 2}] << endl;
    matrix1.MakeSlice({1, 2}, {2, 2}).Print();



//    matrix1.print();
//    matrix1.addRow(matrix2);
//    matrix1.print();

//
//    matrix1.print();
//    cout << endl << matrix1(0, -1);
//
//    matrix1.slice(0, 0, 1, 1).print(); // from (0, 0) to (1, 1)
//    matrix1.slice(0, 0, 2, 0).print(); // first column
//    matrix1.slice(2, -1, 2, 0).print(); // last row reversed
//    matrix1.slice(-1, -1, 0, 0).print(); // reversed matrix


//    matrix1.print();
//    matrix1.transpose();
//    matrix1.print();
//    (~matrix1).print();

//    cout << ;


//    Matrix<int> matrix2 = Matrix<int>(3, 2, {1, -2, 0, 3, 4, -5});
//
//    (matrix1 + -1000).print();


//    Matrix<int> matrix1 = Matrix<int>(10'000, 1000);
//    Matrix<int> matrix2 = Matrix<int>(10'000, 1000);
//
//    vector<int> v1 = vector<int>();
//    vector<int> v2 = vector<int>();
//
//    v1.reserve(100'000);
//
//    high_resolution_clock::time_point t11 = high_resolution_clock::now();
//
//    for (int i = 0; i < 100'000; ++i)
//        v1.push_back(14);
//
//    high_resolution_clock::time_point t12 = high_resolution_clock::now();
//    cout << "Reserve method: " << duration_cast<duration<double>>(t12 - t11).count() << endl;
//
//
//    high_resolution_clock::time_point t21 = high_resolution_clock::now();
//    for (int i = 0; i < 100'000; ++i)
//        v2.push_back(14);
//    high_resolution_clock::time_point t22 = high_resolution_clock::now();
//    cout << "Nor reserve method: " << duration_cast<duration<double>>(t22 - t21).count() << endl;


//    vector<int> vec = {2, 3, -5, 6, 9, -7};
//
//    auto i1 = apply_(vec, [](int a){return 2 * a;}, false);
//
//    for (auto i : i1)
//        cout << i << endl;

    return 0;
}

