#pragma once

#include <vector>
#include <ostream>
#include <iostream>
#include <algorithm>
#include "Utils/Utils.cpp"


namespace LinearAlgebra {
    template<typename T = int>
    class Matrix {
    private: // Private members
        int rowCount;
        int columnCount;
        int capacity;
        std::vector<T> data;

    public:
        #pragma region --Constructors--
        Matrix(int rowCount, int columnCount)
                :
                data(std::vector<T>(rowCount * columnCount)),
                rowCount(rowCount), columnCount(columnCount), capacity(rowCount * columnCount)
        {}

        Matrix(int rowCount, int columnCount, std::vector<T> data)
                : data(move(data)), rowCount(rowCount), columnCount(columnCount), capacity(data.capacity())
        {}

        Matrix(const Matrix<T>& other)
                : data(other.data),
                  rowCount(other.getRowCount()), columnCount(other.getColumnCount()),
                  capacity(other.getCapacity())
        {}
        #pragma endregion

        int getRowCount() const {
            return rowCount;
        }
        int getColumnCount() const {
            return columnCount;
        }
        int getCapacity() const {
            return capacity;
        }

        void transpose();

        T& at(int rowIndex, int columnIndex) {
            return data[columnCount * rowIndex + columnIndex];
        }
        const T& at(int rowIndex, int columnIndex) const {
            return data.at(columnCount * rowIndex + columnIndex);
        }

        T& atSingleIndex(int index) {
            return data[index];
        }
        const T& atSingleIndex(int index) const {
            return data.at(index);
        }

        Matrix<T> slice(int beginRow, int beginColumn, int endRow, int endColumn) {
            int newRowCount = endRow - beginRow + 1;
            int newColumnCount = endColumn - beginColumn + 1;

            std::vector<T> newData(newRowCount * newColumnCount);
            for (int i = beginRow, newDataIndex = 0; i <= endRow; ++i){
                for (int j = beginColumn; j <= endColumn; ++j)
                    newData[newDataIndex++] = at(i, j);
            }
            return Matrix<T>(newRowCount, newColumnCount, newData);
        }

        void print(std::ostream& stream) {
            for (int i = 0; i < rowCount; ++i) {
                for (int j = 0; j < columnCount; ++j)
                    stream << at(i, j) << " ";
                stream << std::endl;
            }
        }
        void print() {
            print(std::cout);
        }

        void fill(const std::vector<T>& vector) {
            if(vector.capacity() != capacity)
                throw std::invalid_argument("Invalid capacity");

            if(vector.size() != rowCount * columnCount)
                throw std::invalid_argument("Invalid vector size");

            data = vector;
        }

        #pragma region --Operators--
        T& operator()(int rowIndex, int columnIndex) {
            return at(rowIndex, columnIndex);
        }
        const T& operator()(int rowIndex, int columnIndex) const {
            return at(rowIndex, columnIndex);
        }

        T& operator()(int index) {
            return data[index];
        }
        const T& operator()(int index) const {
            return data.at(index);
        }


        Matrix<T> operator+(const Matrix<T>& other) {
            return Matrix<T>(
                    rowCount, columnCount,
                    Utils::zip(data, other.data, [](const T& l, const T& r){return l + r;})
            );
        }
        Matrix<T> operator+(const T& constant) {
            auto result = std::vector<T>(data);
            Utils::apply(result, [constant](const T& item){return item + constant;});

            return Matrix<T>(
                    rowCount, columnCount,
                    result
            );
        }

        Matrix<T> operator-(const Matrix<T>& other) {
            return Matrix<T>(
                    rowCount, columnCount,
                    Utils::zip(data, other.data, [](const T& l, const T& r){return l - r;})
            );
        }
        Matrix<T> operator-(const T& constant) {
            return operator+(-constant);
        }

        Matrix<T> operator*(const Matrix<T>& other) {
            // TODO: replace Matrix with std::vector
            Matrix<T> result = Matrix<T>(rowCount, other.getColumnCount());

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
        Matrix<T> operator*(const T& constant) {
            auto result = std::vector<T>(data);
            Utils::apply(result, [constant](const T& item){return item * constant;});

            return Matrix<T>(
                    rowCount, columnCount,
                    result
            );
        }

        Matrix<T> operator/(const T& constant) {
            auto result = std::vector<T>(data);
            Utils::apply(result, [constant](const T& item){return item / constant;});

            return Matrix<T>(
                    rowCount, columnCount,
                    result
            );
        }
        Matrix<T> operator/(const Matrix<T>& other); // TODO: ??


        Matrix<T> operator-() {
            auto result = std::vector<T>(data);
            Utils::apply(result, [](const T& item){return -item;});

            return Matrix<T>(
                    rowCount, columnCount,
                    result
            );
        }
        Matrix<T> operator~() { // Transpose

            // TODO: without this->operator(i, j)
            if(rowCount != columnCount)
                throw std::invalid_argument("Count of rows != count of columns");

            auto result = Matrix<T>(*this);
            for (int i = 0; i < rowCount; ++i)
                for(int j = 0; j < columnCount; ++j)
                    result(j, i) = operator()(i, j);

            return result;
        }

        Matrix<T>& operator+=(const Matrix<T>& other) {
            for (int i = 0; i < capacity; ++i)
                data[i] += other.data[i];
            return *this;
        }
        Matrix<T>& operator-=(const Matrix<T>& other) {
            for (int i = 0; i < capacity; ++i)
                data[i] -= other.data[i];
            return *this;
        }
        Matrix<T>& operator*=(const Matrix<T>& other) {
            for (int i = 0; i < capacity; ++i)
                data[i] *= other.data[i];
            return *this;
        }
        Matrix<T>& operator/=(const Matrix<T>& other) {
            for (int i = 0; i < capacity; ++i)
                data[i] /= other.data[i];
            return *this;
        }

        Matrix<T>& operator+=(const T& constant) {
            for (auto& item : data)
                item += constant;
            return *this;
        }
        Matrix<T>& operator-=(const T& constant) {
            for (auto& item : data)
                item -= constant;
            return *this;
        }
        Matrix<T>& operator*=(const T& constant) {
            for (auto& item : data)
                item *= constant;
            return *this;
        }
        Matrix<T>& operator/=(const T& constant) {
            for (auto& item : data)
                item /= constant;
            return *this;
        }

        Matrix<T>& operator&=(const Matrix<T>& other) {
            for (int i = 0; i < capacity; ++i)
                data[i] &= other.data[i];
            return *this;
        }
        Matrix<T>& operator%=(const Matrix<T>& other) {
            for (int i = 0; i < capacity; ++i)
                data[i] %= other.data[i];
            return *this;
        }
        Matrix<T>& operator^=(const Matrix<T>& other) {
            for (int i = 0; i < capacity; ++i)
                data[i] ^= other.data[i];
            return *this;
        }

        #pragma endregion
    };
}