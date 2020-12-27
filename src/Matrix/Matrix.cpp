#pragma once
#include "Matrix.h"
#include <iostream>

using namespace LinearAlgebra;


#pragma region --Constructors--
template<typename type>
Matrix<type>::Matrix(int rowCount, int columnCount)
    :
    data(std::vector<type>(rowCount * columnCount)),
    rowCount(rowCount), columnCount(columnCount), capacity(rowCount * columnCount)
    {}

template<typename type>
Matrix<type>::Matrix(int rowCount, int columnCount, std::vector<type> data)
    : data(move(data)), rowCount(rowCount), columnCount(columnCount), capacity(data.capacity())
    {}

template<typename type>
Matrix<type>::Matrix(const Matrix<type>& other)
        : data(other.data),
        rowCount(other.getRowCount()), columnCount(other.getColumnCount()),
        capacity(other.getCapacity())
{}
#pragma endregion

#pragma region --Getters--
template<typename type>
int Matrix<type>::getRowCount() const {
    return rowCount;
}

template<typename type>
int Matrix<type>::getColumnCount() const {
    return columnCount;
}

template<typename type>
int Matrix<type>::getCapacity() const {
    return capacity;
}
#pragma endregion

#pragma region --Methods--
template<typename type>
type& Matrix<type>::at(int rowIndex, int columnIndex) {
    return data[columnCount * rowIndex + columnIndex];
}

template<typename type>
const type& Matrix<type>::at(int rowIndex, int columnIndex) const {
    return data.at(columnCount * rowIndex + columnIndex);
}

template<typename type>
type& Matrix<type>::atSingleIndex(int index) {
    return data[index];
}

template<typename type>
const type& Matrix<type>::atSingleIndex(int index) const {
    return data.at(index);
}

template<typename type>
std::vector<type> Matrix<type>::at(Slice slice) {
    return std::vector<type>(
        data.begin() + slice.getBegin(),
        data.begin() + slice.getBegin() + slice.getEnd()
    );
}

template<typename type>
Matrix<type> Matrix<type>::at(Slice2d slice) {
    int newRowCount = slice.endRow - slice.beginRow + 1;
    int newColumnCount = slice.endColumn - slice.beginColumn + 1;

    std::vector<type> newData(newRowCount * newColumnCount);
    for (int i = slice.beginRow, newDataIndex = 0; i <= slice.endRow; ++i){
        for (int j = slice.beginColumn; j <= slice.endColumn; ++j)
            newData[newDataIndex++] = at(i, j);
    }
    return Matrix<type>(newRowCount, newColumnCount, newData);
}

template<typename type>
void Matrix<type>::print(std::ostream& stream) {
    for (int i = 0; i < rowCount; ++i) {
        for (int j = 0; j < columnCount; ++j)
            stream << at(i, j) << " ";
        stream << std::endl;
    }
}

template<typename type>
void Matrix<type>::print() {
    print(std::cout);
}

template<typename type>
void Matrix<type>::fill(const std::vector<type>& vector) {
    if(vector.capacity() != capacity)
        throw std::invalid_argument("Invalid capacity");

    if(vector.size() != rowCount * columnCount)
        throw std::invalid_argument("Invalid vector size");

    data = vector;
}
#pragma endregion

#pragma region --Operators--
template<typename type>
type& Matrix<type>::operator()(int rowIndex, int columnIndex) {
    return at(rowIndex, columnIndex);
}

template<typename type>
const type& Matrix<type>::operator()(int rowIndex, int columnIndex) const {
    return at(rowIndex, columnIndex);
}

template<typename type>
type& Matrix<type>::operator()(int index) {
    return data[index];
}

template<typename type>
const type& Matrix<type>::operator()(int index) const {
    return data.at(index);
}

template<typename type>
Matrix<type> Matrix<type>::operator+(const Matrix<type>& other) {
    Matrix<type> result = Matrix<type>(*this);

    for(int i = 0; i < capacity; i++)
        result(i) += other(i);

    return result;
}


template<typename type>
Matrix<type> Matrix<type>::operator+(const type& constant) {
    std::vector<type> resultVector = std::vector<type>(data);
    for (int i = 0; i < capacity; ++i)
        resultVector[i] += constant;

    return Matrix<type>(rowCount, columnCount, resultVector);
}

template<typename type>
Matrix<type> Matrix<type>::operator*(const Matrix<type>& other) {
    Matrix<type> result = Matrix<type>(rowCount, other.getColumnCount());

    for (int otherColumnIndex = 0; otherColumnIndex < other.getColumnCount(); ++otherColumnIndex) {
        for (int rowIndex = 0; rowIndex < rowCount; ++rowIndex) {
            for (int otherRowIndex = 0; otherRowIndex < other.getRowCount(); ++otherRowIndex) {
                result(rowIndex, otherColumnIndex) +=
                    at(rowIndex, otherRowIndex) * other.at(otherRowIndex, otherColumnIndex);
            }
        }
    }

    return result;
}

template<typename type>
Matrix<type> Matrix<type>::operator*(const type& constant) {
    std::vector<type> resultVector = std::vector<type>(data);

    for (int i = 0; i < capacity; ++i)
        resultVector[i] *= constant;

    return Matrix<type>(rowCount, columnCount, resultVector);
}

template<typename type>
Matrix<type> Matrix<type>::smatrix(const type& constant) {
    Matrix<type> result = Matrix<type>(*this);

    for (int i = 0; i < rowCount; ++i) {
        for (int j = 0; j < columnCount; ++j) {
            result(i, j) += constant;
        }
    }
    return result;

}

template<typename type>
Matrix<type> Matrix<type>::svector(const type& constant) {
    // Эффективно но не понятно
    std::vector<type> resultVector = std::vector<type>(data);
    for (int i = 0; i < capacity; ++i)
        resultVector[i] += constant;

    return Matrix<type>(rowCount, columnCount, resultVector);
}


#pragma endregion
