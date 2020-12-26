#include "library.cpp"
#include <iostream>
using namespace LinearAlgebra;
using namespace std;

int main(){
    Matrix<2, 2> matrix1 = Matrix<2, 2>({1, 2, 3, 4});
    Matrix<2, 2> matrix2 = Matrix<2, 2>({99, 2, 3, -8});

    (matrix1 + matrix2).print();

    return 0;
}

