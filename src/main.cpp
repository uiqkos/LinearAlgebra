
#include "Matrix/Matrix.cpp"
#include <iostream>

using namespace LinearAlgebra;
using namespace std;

int main(){
    vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    Matrix<int> matrix = Matrix<int>(5, 4, vec);
    auto m = matrix.at(Slice2d(1, 3, 1, 3));
    m.print();
    return 0;
}

