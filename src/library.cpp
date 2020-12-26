#include "library.h"

#include <iostream>
#include <exception>

using namespace LinearAlgebra;

#define MatrixType Matrix<rows, columns, type>


// Constructors
template<int rows, int columns, typename type>
Matrix<rows, columns, type>::Matrix()
    :
    data(std::vector<type>(rows * columns)),
    rowCount(rows), columnCount(columns), capacity(rows * columns)
    {}

template<int rows, int columns, typename type>
Matrix<rows, columns, type>::Matrix(std::vector<type> data)
    : data(move(data)), rowCount(rows), columnCount(columns), capacity(data.capacity())
    {}

template<int rows, int columns, typename type>
Matrix<rows, columns, type>::Matrix(const MatrixType& other)
        : Matrix<rows, columns, type>(other.data)
{}


// Getters
template<int rows, int columns, typename type>
int Matrix<rows, columns, type>::getRowCount() const {
    return rowCount;
}

template<int rows, int columns, typename type>
int Matrix<rows, columns, type>::getColumnCount() const {
    return columnCount;
}

template<int rows, int columns, typename type>
int Matrix<rows, columns, type>::getCapacity() const {
    return capacity;
}


// Methods
template<int rows, int columns, typename type>
type& Matrix<rows, columns, type>::at(int rowIndex, int columnIndex) {
    return data[rowCount * rowIndex + columnIndex];
}

template<int rows, int columns, typename type>
const type& Matrix<rows, columns, type>::at(int rowIndex, int columnIndex) const {
    return data.at(rowCount * rowIndex + columnIndex);
}

template<int rows, int columns, typename type>
type& Matrix<rows, columns, type>::atSingleIndex(int index) {
    return data[index];
}

template<int rows, int columns, typename type>
const type& Matrix<rows, columns, type>::atSingleIndex(int index) const {
    return data.at(index);
}

template<int rows, int columns, typename type>
void Matrix<rows, columns, type>::print(std::ostream& stream) {
    for (int i = 0; i < columnCount; ++i) {
        for (int j = 0; j < rowCount; ++j)
            stream << at(i, j) << " ";
        stream << std::endl;
    }
}

template<int rows, int columns, typename type>
void Matrix<rows, columns, type>::print() {
    print(std::cout);
}

template<int rows, int columns, typename type>
void Matrix<rows, columns, type>::fill(const std::vector<type>& vector) {
    if(vector.capacity() != capacity)
        throw std::invalid_argument("Invalid capacity");

    if(vector.size() != rowCount * columnCount)
        throw std::invalid_argument("Invalid vector size");

    data = vector;
}


// Operators
template<int rows, int columns, typename type>
type& Matrix<rows, columns, type>::operator()(int rowIndex, int columnIndex) {
    return at(rowIndex, columnIndex);
}

template<int rows, int columns, typename type>
const type& Matrix<rows, columns, type>::operator()(int rowIndex, int columnIndex) const {
    return at(rowIndex, columnIndex);
}

template<int rows, int columns, typename type>
type& Matrix<rows, columns, type>::operator()(int index) {
    return data[index];
}

template<int rows, int columns, typename type>
const type& Matrix<rows, columns, type>::operator()(int index) const {
    return data.at(index);
}

template<int rows, int columns, typename type>
MatrixType MatrixType::operator+(const MatrixType& other) {
    MatrixType result = Matrix<rows, columns, type>(*this);
    for(int i = 0; i < result.getCapacity(); i++){
        result(i) += other(i);
    }
    return result;
}

