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

        bool canTranspose() {
            return rowCount == columnCount;
        }

        void transpose() {
            if(rowCount != columnCount)
                throw std::invalid_argument("Count of rows != count of columns");

            for (int i = 0; i < rowCount; i++)
                for (int j = i; j < columnCount; ++j)
                    std::swap(at(i, j), at(j, i));
        }

        T& at(int rowIndex, int columnIndex) {
            if (rowIndex < 0) rowIndex += rowCount;
            if (columnIndex < 0) columnIndex += columnCount;

            return data[columnCount * rowIndex + columnIndex];
        }
        const T& at(int rowIndex, int columnIndex) const {
            if (rowIndex < 0) rowIndex += rowCount;
            if (columnIndex < 0) columnIndex += columnCount;

            return data.at(columnCount * rowIndex + columnIndex);
        }

        T& atSingleIndex(int index) {
            if(index < 0) index += capacity;
            return data[index];
        }
        const T& atSingleIndex(int index) const {
            if(index < 0) index += capacity;
            return data.at(index);
        }

        Matrix<T> slice(int beginRow, int beginColumn, int endRow, int endColumn) {

            // Check for negative
            if (beginRow < 0)     beginRow    += rowCount;
            if (beginColumn < 0)  beginColumn += columnCount;
            if (endRow < 0)       endRow      += rowCount;
            if (endColumn < 0)    endColumn   += columnCount;


            int newRowCount = abs(endRow - beginRow) + 1;
            int newColumnCount = abs(endColumn - beginColumn) + 1;

            int rowShift = endRow < beginRow ? -1 : 1;
            int columnShift = endColumn < beginColumn ? -1 : 1;


            std::vector<T> newData(newRowCount * newColumnCount);
            int newDataIndex = 0;
            for (int row = beginRow; Utils::inRange(beginRow, endRow, row); row += rowShift)
                for (int column = beginColumn; Utils::inRange(beginColumn, endColumn, column); column += columnShift)
                    newData[newDataIndex++] = at(row, column);

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

        friend std::ostream& operator<<(std::ostream& stream, Matrix<T> matrix) {
            matrix.print(stream);
            return stream;
        }

        friend bool operator==(Matrix<T> first, Matrix<T> second) {
            return
                first.data == second.data and
                first.rowCount == second.rowCount and
                first.columnCount == second.columnCount;
        }
        friend bool operator!=(Matrix<T> first, Matrix<T> second) {
            return !(first == second);
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
                    result(j, i) = at(i, j);

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