#include <iostream>
#include <algorithm>
#include <ctime>
#include <ratio>
#include <chrono>

#include "Matrix/Matrix.h"
//#include "Utils/Utils.cpp"
#include "Fraction/Fraction.h"

using namespace LinearAlgebra;
using namespace Utils;
using namespace std::chrono;
using namespace std;

int main(){

//    Matrix<double> matrix2 = Matrix(matrix);
//    Matrix<Fraction<int>> matrix = Matrix(2, 2, vector<Fraction<int>>{{1, 2}, {1, 3}, {2, 6}, {1, 1}});
//    matrix2.Print();

    Matrix matrix1 = Matrix(3, 3, vector<int>{1, 2, 3, 0, 4, 5, 1, 0, 6});
//    matrix1.Print();
//    cout << "Det = " << matrix1.Det() << endl;
//    Transpose(matrix1).Print();
//    Inverse(matrix1).Print();

//    Matrix matrix2 = Matrix(3, 2, vector<int>{-5, -7, 9, 6, -9, -9});
//    (matrix1 * matrix2).Print();
//    Multiply(matrix1, matrix2).Print();
//    Matrix matrix3 = Matrix(3, 0);

//    cout << Determinant(matrix1);


//    ConcatHorizontal(matrix2, matrix3).Print();
//
//    matrix1.MakeSlice({0, 3}, {-1, 3}).Print();

//    cout << matrix1[{1, 2}] << endl;
//    matrix1.MakeSlice(-1, -1, -1, 0).Print();
//    matrix1.Print();
//    matrix1.MakeSlice(1, 0, -1, -2).Print();
//    ConcatHorizontal(matrix1, matrix2);
//    ConcatHorizontal(matrix1, matrix2).Print();
//    ConcatVertical(matrix1, matrix3).Print();
//    matrix1.AddRow({1, 2, 3});
//
//    matrix1.Print();
//
//    auto vec = matrix1.GetRow(2);
//    auto vec2 = matrix1.GetRow(0);

//    matrix1.print();
//    matrix1.addRow(matrix2);
//    matrix1.print();

//
//    matrix1.print();
//    cout << endl << matrix1(0, -1);
//
    matrix1.MakeSlice(0, 0, 1, 1).Print(); // from (0, 0) to (1, 1)
    matrix1.MakeSlice(0, 0, -1, 0).Print(); // first column
    matrix1.MakeSlice(-1, -1, -1, 0).Print(); // last row reversed
    matrix1.MakeSlice(-1, -1, 0, 0).Print(); // reversed matrix


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

