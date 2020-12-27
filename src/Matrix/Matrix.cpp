#pragma once
#include "Matrix.h"
#include <iostream>

using namespace LinearAlgebra;

#define MatrixType Matrix<type>


#pragma region --Constructors--
template<typename type>
MatrixType::Matrix(int rowCount, int columnCount)
    :
    data(std::vector<type>(rowCount * columnCount)),
    rowCount(rowCount), columnCount(columnCount), capacity(rowCount * columnCount)
    {}

template<typename type>
MatrixType::Matrix(int rowCount, int columnCount, std::vector<type> data)
    : data(move(data)), rowCount(rowCount), columnCount(columnCount), capacity(data.capacity())
    {}

template<typename type>
MatrixType::Matrix(const MatrixType& other)
        : data(other.data),
        rowCount(other.getRowCount()), columnCount(other.getColumnCount()),
        capacity(other.getCapacity())
{}
#pragma endregion

#pragma region --Getters--
template<typename type>
int MatrixType::getRowCount() const {
    return rowCount;
}

template<typename type>
int MatrixType::getColumnCount() const {
    return columnCount;
}

template<typename type>
int MatrixType::getCapacity() const {
    return capacity;
}
#pragma endregion

#pragma region --Methods--
template<typename type>
type& MatrixType::at(int rowIndex, int columnIndex) {
    return data[rowCount * rowIndex + columnIndex];
}

template<typename type>
const type& MatrixType::at(int rowIndex, int columnIndex) const {
    return data.at(rowCount * rowIndex + columnIndex);
}

template<typename type>
type& MatrixType::atSingleIndex(int index) {
    return data[index];
}

template<typename type>
const type& MatrixType::atSingleIndex(int index) const {
    return data.at(index);
}


template<typename type>
MatrixType MatrixType::at(Slice2d slice) {
    int newRowCount = slice.endRow - slice.beginRow;
    int newColumnCount = slice.endColumn - slice.beginColumn;

    std::vector<type> newData(newRowCount * newColumnCount);
    for (int i = slice.beginRow, newDataIndex = 0; i < slice.endRow; ++i){
        for (int j = slice.beginColumn; j < slice.endColumn; ++j)
            newData[newDataIndex++] = at(i, j);
    }
    return Matrix<type>(newRowCount, newColumnCount, newData);
}

template<typename type>
void MatrixType::print(std::ostream& stream) {
    for (int i = 0; i < columnCount; ++i) {
        for (int j = 0; j < rowCount; ++j)
            stream << at(i, j) << " ";
        stream << std::endl;
    }
}

template<typename type>
void MatrixType::print() {
    print(std::cout);
}

template<typename type>
void MatrixType::fill(const std::vector<type>& vector) {
    if(vector.capacity() != capacity)
        throw std::invalid_argument("Invalid capacity");

    if(vector.size() != rowCount * columnCount)
        throw std::invalid_argument("Invalid vector size");

    data = vector;
}
#pragma endregion

#pragma region --Operators--
template<typename type>
type& MatrixType::operator()(int rowIndex, int columnIndex) {
    return at(rowIndex, columnIndex);
}

template<typename type>
const type& MatrixType::operator()(int rowIndex, int columnIndex) const {
    return at(rowIndex, columnIndex);
}

template<typename type>
type& MatrixType::operator()(int index) {
    return data[index];
}

template<typename type>
const type& MatrixType::operator()(int index) const {
    return data.at(index);
}

template<typename type>
MatrixType MatrixType::operator+(const MatrixType& other) {
    MatrixType result = MatrixType(*this);
    for(int i = 0; i < result.getCapacity(); i++){
        result(i) += other(i);
    }
    return result;
}

template<typename type>
MatrixType MatrixType::operator*(const MatrixType& other) {
    Matrix<type> result
        = Matrix<type>();
    return result;
}

#pragma endregion
