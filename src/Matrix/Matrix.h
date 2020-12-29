#pragma once

#include <vector>
#include <string>
//#include <format>
#include <ostream>
#include <iostream>
#include <algorithm>

#include "Slice/Slice.h"
#include "Utils/Utils.cpp"


namespace LinearAlgebra {
    template<typename T = int>
    class Matrix {
    private: // Private members
        int rowCount;
        int columnCount;
        int capacity;
        std::vector<T> data;

    public: // Getters
        int GetRowCount() const {
            return rowCount;
        }
        int GetColumnCount() const {
            return columnCount;
        }
        int GetCapacity() const {
            return capacity;
        }
        std::pair<int, int> Shape() {
            return std::make_pair(rowCount, columnCount);
        }

    private:
        bool InRange(int left, int right, int value) {
            if (left < right)
                return left <= value and value <= right;

            return right <= value and value <= left;
        }

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

        /////////////// Element access ///////////////

        T& At(int rowIndex, int columnIndex) {
            if (rowIndex < 0) rowIndex += rowCount;
            if (columnIndex < 0) columnIndex += columnCount;

            return data[columnCount * rowIndex + columnIndex];
        }
        const T& At(int rowIndex, int columnIndex) const {
            if (rowIndex < 0) rowIndex += rowCount;
            if (columnIndex < 0) columnIndex += columnCount;

            return data.At(columnCount * rowIndex + columnIndex);
        }

        T& At(Index index) {
            return At(index.row, index.column);
        }
        const T& At(Index index) const {
            return At(index.row, index.column);
        }

        T& AtSingleIndex(int index) {
            if(index < 0) index += capacity;
            return data[index];
        }
        const T& AtSingleIndex(int index) const {
            if(index < 0) index += capacity;
            return data.At(index);
        }

        T& operator()(int rowIndex, int columnIndex) {
            return At(rowIndex, columnIndex);
        }
        const T& operator()(int rowIndex, int columnIndex) const {
            return At(rowIndex, columnIndex);
        }

        T& operator[](Index index) {
            return At(index);
        }
        Matrix<T> operator[](Slice slice) {
            return MakeSlice(slice);
        }

        Matrix<T> MakeSlice(int beginRow, int beginColumn, int endRow, int endColumn) {

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
            for (int row = beginRow; InRange(beginRow, endRow, row); row += rowShift)
                for (int column = beginColumn; InRange(beginColumn, endColumn, column); column += columnShift)
                    newData[newDataIndex++] = At(row, column);

            return Matrix<T>(newRowCount, newColumnCount, newData);
        }
        Matrix<T> MakeSlice(Index begin, Index end) {
            return MakeSlice(begin.row, begin.column, end.row, end.column);
        }
        Matrix<T> MakeSlice(Slice slice) {
            return MakeSlice(slice.begin, slice.end);
        }

        /////////////// Transpose ///////////////
        bool CanTranspose() {
            return rowCount == columnCount;
        }
        void Transpose() {
            if(rowCount != columnCount)
                throw std::invalid_argument("Count of rows != count of columns");

            for (int i = 0; i < rowCount; i++)
                for (int j = i; j < columnCount; ++j)
                    std::swap(At(i, j), At(j, i));
        }
        friend Matrix<T> Transpose(Matrix<T> matrix) {

            // TODO: without this->operator(i, j)
            if(!matrix.CanTranspose())
                throw std::invalid_argument("Count of rows != count of columns");

            auto result = Matrix<T>(matrix);
            for (int i = 0; i < matrix.rowCount; ++i)
                for(int j = 0; j < matrix.columnCount; ++j)
                    result(j, i) = matrix.At(i, j);

            return result;
        }

        Matrix<T> operator~() {
            return Transpose(*this);
        }

        void Reshape(int newRowCount, int newColumnCount) {
            if (newRowCount * newColumnCount != capacity)
                throw std::invalid_argument("Invalid operation");

            rowCount = newRowCount;
            columnCount = newColumnCount;
        }
        void Reshape(std::pair<int, int> shape) {
            Reshape(shape.first, shape.second);
        }

        /////////////// Print ///////////////
        void Print(std::ostream& stream) {
            for (int i = 0; i < rowCount; ++i) {
                for (int j = 0; j < columnCount; ++j)
                    stream << At(i, j) << " ";
                stream << std::endl;
            }
        }
        void Print() {
            Print(std::cout);
        }

        friend std::ostream& operator<<(std::ostream& stream, Matrix<T> matrix) {
            matrix.Print(stream);
            return stream;
        }

        /////////////// Fill ///////////////
        void Fill(const std::vector<T>& vector) {
            if(vector.capacity() != capacity)
                throw std::invalid_argument("Invalid capacity");

            if(vector.size() != rowCount * columnCount)
                throw std::invalid_argument("Invalid vector size");

            data = vector;
        }

        #pragma region --Operators--
        /////////////// Bool operators ///////////////
        friend bool operator==(Matrix<T> first, Matrix<T> second) {
            return
                first.data == second.data and
                first.rowCount == second.rowCount and
                first.columnCount == second.columnCount;
        }
        friend bool operator!=(Matrix<T> first, Matrix<T> second) {
            return !(first == second);
        }

        /////////////// Arithmetic ///////////////
        Matrix<T> operator+(const Matrix<T>& other) {
            return Matrix<T>(
                rowCount, columnCount,
                Utils::Zip(data, other.data, [](const T& l, const T& r){return l + r;})
            );
        }
        Matrix<T> operator+(const T& constant) {
            auto result = std::vector<T>(data);
            Utils::Apply(result, [constant](const T& item){return item + constant;});

            return Matrix<T>(
                rowCount, columnCount,
                result
            );
        }

        Matrix<T> operator-(const Matrix<T>& other) {
            return Matrix<T>(
                    rowCount, columnCount,
                    Utils::Zip(data, other.data, [](const T& l, const T& r){return l - r;})
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
                                At(rowIndex, otherRowIndex) * other.At(otherRowIndex, otherColumnIndex);
                    }
                }
            }

            return result;
        }
        Matrix<T> operator*(const T& constant) {
            auto result = std::vector<T>(data);
            Utils::Apply(result, [constant](const T& item){return item * constant;});

            return Matrix<T>(
                rowCount, columnCount,
                result
            );
        }

        Matrix<T> operator/(const Matrix<T>& other); // TODO: ??

        Matrix<T> operator-() {
            auto result = std::vector<T>(data);
            Utils::Apply(result, [](const T& item){return -item;});

            return Matrix<T>(
                rowCount, columnCount,
                result
            );
        }

        /////////////// Assigment operators ///////////////
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