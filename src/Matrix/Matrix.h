
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedGlobalDeclarationInspection"
#pragma once

#include <vector>
#include <string>
#include <ostream>
#include <iostream>
#include <algorithm>

#include "Slice/Slice.h"
#include "Utils/Utils.cpp"


namespace LinearAlgebra {
    template<typename T = int>
    class Matrix {
    private:
        /*/////////////// Private members ///////////////*/

        int rowCount;
        int columnCount;
        int capacity;
        std::vector<T> data;

    public:
        /*/////////////// Getters ///////////////*/

        int GetRowCount() const {
            return rowCount;
        }
        int GetColumnCount() const {
            return columnCount;
        }
        int GetCapacity() const {
            return capacity;
        }
        std::pair<int, int> Shape() const {
            return std::make_pair(rowCount, columnCount);
        }

    private:
        static bool InRange(int left, int right, int value) {
            if (left < right)
                return left <= value and value <= right;

            return right <= value and value <= left;
        }

    private:
        /*/////////////// Asserts and checks ///////////////*/
        /*// Asserts //*/
        /* Rows */
        void _assert_rows_equals(int otherRowCount) const {
            if (rowCount != otherRowCount)
                throw std::invalid_argument("The number of rows does not match");
        }
        static void _assert_rows_equals(const Matrix<T>& first, const Matrix<T>& second) {
            if (first.rowCount != second.rowCount)
                throw std::invalid_argument("The number of rows does not match");
        }
        void _assert_row_index_in_range(int index) const {
            if (!InRange(-rowCount, rowCount, index))
                throw std::invalid_argument("Row index out of range");
        }
        /* Columns */
        void _assert_columns_equals(int otherColumnCount) const {
            if (columnCount != otherColumnCount)
                throw std::invalid_argument("The number of columns does not match");
        }
        static void _assert_columns_equals(const Matrix<T>& first, const Matrix<T>& second) {
            if (first.columnCount != second.columnCount)
                throw std::invalid_argument("The number of columns does not match");
        }
        void _assert_column_index_in_range(int index) const {
            if (!InRange(-columnCount, columnCount, index))
                throw std::invalid_argument("Column index out of range");
        }
        /* Shape */
        void _assert_shape_equals(const Matrix<T>& other) const {
            if (rowCount != other.rowCount or columnCount != other.columnCount)
                throw std::invalid_argument("Shapes are not equal");
        }
        static void _assert_shape_equals(const Matrix<T>& matrix, std::pair<int, int> shape) {
            if (matrix.Shape() != shape)
                throw std::invalid_argument("Shapes are not equal");
        }
        static void _assert_square(const Matrix<T>& matrix) {
            if (matrix.rowCount != matrix.columnCount)
                throw std::invalid_argument("Matrix is not square");
        }


        /*// Checks //*/
        static bool _check_square(const Matrix<T>& matrix) {
            return matrix.rowCount == matrix.columnCount;
        }
        static bool _check_square2x2(const Matrix<T>& matrix) {
            return matrix.rowCount == 2 and matrix.columnCount == 2;
        }

    public:
        #pragma region --Constructors--
        /*/////////////// Constructors ///////////////*/

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
                  rowCount(other.GetRowCount()), columnCount(other.GetColumnCount()),
                  capacity(other.GetCapacity())
        {}
        #pragma endregion

        #pragma region --Methods--
        /*/////////////// Element access ///////////////*/

        T& At(int rowIndex, int columnIndex) {
            if (rowIndex < 0) rowIndex += rowCount;
            if (columnIndex < 0) columnIndex += columnCount;

            return data[columnCount * rowIndex + columnIndex];
        }
        const T& At(int rowIndex, int columnIndex) const {
            if (rowIndex < 0) rowIndex += rowCount;
            if (columnIndex < 0) columnIndex += columnCount;

            return data.at(columnCount * rowIndex + columnIndex);
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

        Matrix<T> GetRow(int rowIndex) const {
            _assert_row_index_in_range(rowIndex);
            return Matrix<T>(
                1, columnCount,
                std::vector<T>(
                    data.begin() + columnCount * rowIndex,
                    data.begin() + columnCount * rowIndex + columnCount
                )
            );
        }

        Matrix<T> GetColumn(int columnIndex) const {
            _assert_column_index_in_range(columnIndex);
            auto resultVector = std::vector<T>();
            for (int rowIndex = 0; rowIndex < rowCount; ++rowIndex)
                resultVector.push_back(At(rowIndex, columnIndex));
            return Matrix<T>(rowCount, 1, resultVector);
        }

        /*/////////////// Slices ///////////////*/

        Matrix<T> MakeSlice(int beginRow, int beginColumn, int endRow, int endColumn) const {
            _assert_row_index_in_range(beginRow);
            _assert_column_index_in_range(beginColumn);

            _assert_row_index_in_range(endRow);
            _assert_column_index_in_range(endColumn);

            // Check for negative
            if (beginRow < 0)     beginRow    += rowCount;
            if (beginColumn < 0)  beginColumn += columnCount;
            if (endRow < 0)       endRow      += rowCount;
            if (endColumn < 0)    endColumn   += columnCount;

            int newRowCount = abs(endRow - beginRow) + 1;
            int newColumnCount = abs(endColumn - beginColumn) + 1;

            if (newRowCount == 0 or newColumnCount == 0)
                return Matrix<T>(newRowCount, newColumnCount);

            int rowShift = endRow < beginRow ? -1 : 1;
            int columnShift = endColumn < beginColumn ? -1 : 1;

            std::vector<T> newData(newRowCount * newColumnCount);
            int newDataIndex = 0;
            for (int row = beginRow; InRange(beginRow, endRow, row); row += rowShift)
                for (int column = beginColumn; InRange(beginColumn, endColumn, column); column += columnShift)
                    newData[newDataIndex++] = At(row, column);

            return Matrix<T>(newRowCount, newColumnCount, newData);
        }
        Matrix<T> MakeSlice(Index begin, Index end) const {
            return MakeSlice(begin.row, begin.column, end.row, end.column);
        }
        Matrix<T> MakeSlice(Slice slice) const {
            return MakeSlice(slice.begin, slice.end);
        }

        /*/////////////// Concat and Append ///////////////*/

        void AddRow(const std::vector<T>& row) {
            _assert_columns_equals(row.size());
            data.insert(data.end(), row.begin(), row.end());
            rowCount++;
        }
        void AddRow(const Matrix<T> matrix) {
            _assert_shape_equals(matrix, {1, columnCount});
            AddRow(matrix.data);
        }

        void AddColumn(const std::vector<T> column) {
            _assert_rows_equals(column.size());
            columnCount++;
            for (int rowIndex = 0; rowIndex < rowCount; ++rowIndex)
                data.insert()(data.begin() + columnCount, column[rowIndex]);
        }

        friend Matrix<T> ConcatHorizontal(const Matrix<T>& left, const Matrix<T>& right) {
            _assert_rows_equals(left, right);
            auto result = Matrix<T>(left.rowCount, left.columnCount + right.columnCount);

            for (int rowIndex = 0; rowIndex < left.rowCount; ++rowIndex) {
                // Left columns
                for (int leftColumnIndex = 0; leftColumnIndex < left.columnCount; ++leftColumnIndex)
                    result(rowIndex, leftColumnIndex) = left(rowIndex, leftColumnIndex);

                // Right columns
                for (int rightColumnIndex = 0; rightColumnIndex < right.columnCount; ++rightColumnIndex)
                    result(rowIndex, left.columnCount + rightColumnIndex) = right(rowIndex, rightColumnIndex);
            }
            return result;
        }
        friend Matrix<T> ConcatVertical(const Matrix<T>& up, const Matrix<T>& down) {
            _assert_columns_equals(up, down);
            std::vector<T> resultVector = up.data;
            resultVector.insert(resultVector.end(), down.data.begin(), down.data.end());
            return Matrix<T>(up.rowCount + down.rowCount, up.columnCount, resultVector);
        }

        /*/////////////// Determinant ///////////////*/

        T Det() const {
            return Determinant(*this);
        }

        friend T Determinant(const Matrix<T>& matrix) {
            _assert_square(matrix);

            if (_check_square2x2(matrix))
                return matrix(0, 0) * matrix(1, 1) - matrix(1, 0) * matrix(0, 1);

            T determinant = static_cast<T>(0);

            determinant += matrix(0, 0) * Determinant(matrix.MakeSlice(1, 1, -1, -1));

            // if columnIndex = 0
            // 0  0  0  0
            // 0  #  #  #
            // 0  #  #  #
            // 0  #  #  #

            for (int columnIndex = 1; columnIndex < matrix.columnCount - 1; ++columnIndex) {
                auto t1 = matrix.MakeSlice({1, 0}, {-1, columnIndex - 1});
                auto t2 = matrix.MakeSlice({1, columnIndex + 1}, {-1, matrix.columnCount - 1});
                // if columnIndex = 1
                // 0  0  0  0
                // t1 0  t2 t2
                // t1 0  t2 t2
                // t1 0  t2 t2
                determinant += matrix(0, columnIndex) * Determinant(ConcatHorizontal(t1, t2)) * pow(-1, columnIndex);
            }

            determinant += matrix(0, -1) * Determinant(matrix.MakeSlice(1, 0, -1, -2)) * pow(-1, matrix.GetColumnCount() - 1);

            // if columnIndex = columnCount
            // 0  0  0  0
            // #  #  #  0
            // #  #  #  0
            // #  #  #  0

            return determinant;
        }

        /*/////////////// Inverse ///////////////*/

        // TODO: inverse matrix with fractions

        /*/////////////// Multiplication ///////////////*/

        Matrix<T> Multiply(Matrix<T> left, Matrix<T> right) {
            Matrix<T> result = Matrix<T>(left.rowCount, right.getColumnCount());

            for (int rightColumnIndex = 0; rightColumnIndex < right.getColumnCount(); ++rightColumnIndex) {
                for (int leftRowIndex = 0; leftRowIndex < left.rowCount; ++leftRowIndex) {
                    for (int rightRowIndex = 0; rightRowIndex < right.getRowCount(); ++rightRowIndex) {
                        result(leftRowIndex, rightColumnIndex) +=
                                left(leftRowIndex, rightRowIndex) * right(rightRowIndex, rightColumnIndex);
                    }
                }
            }

            return result;
        }

        Matrix<T> operator*(const Matrix<T>& other) {
            // TODO: replace Matrix with std::vector
            return Multiply(*this, other);
        }

        /*/////////////// Transpose ///////////////*/

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

        /*/////////////// Reshape ///////////////*/

        void Reshape(int newRowCount, int newColumnCount) {
            if (newRowCount * newColumnCount != capacity)
                throw std::invalid_argument("Invalid operation");

            rowCount = newRowCount;
            columnCount = newColumnCount;
        }
        void Reshape(std::pair<int, int> shape) {
            Reshape(shape.first, shape.second);
        }

        /*/////////////// Print ///////////////*/

        void Print(std::ostream& stream) {
            for (int i = 0; i < rowCount; ++i) {
                for (int j = 0; j < columnCount; ++j)
                    stream << At(i, j) << " ";
                stream << std::endl;
            } stream << std::endl;
        }
        void Print() {
            Print(std::cout);
        }

        friend std::ostream& operator<<(std::ostream& stream, Matrix<T> matrix) {
            matrix.Print(stream);
            return stream;
        }

        /*/////////////// Fill ///////////////*/
        void Fill(const std::vector<T>& vector) {
            if(vector.capacity() != capacity)
                throw std::invalid_argument("Invalid capacity");

            if(vector.size() != rowCount * columnCount)
                throw std::invalid_argument("Invalid vector size");

            data = vector;
        }

        void Fill(T newItem) {
            for (auto& item : data)
                item = newItem;
        }

        #pragma endregion

        #pragma region --Operators--
        /*/////////////// Bool operators ///////////////*/

        friend bool operator==(Matrix<T> first, Matrix<T> second) {
            return
                first.data == second.data and
                first.rowCount == second.rowCount and
                first.columnCount == second.columnCount;
        }
        friend bool operator!=(Matrix<T> first, Matrix<T> second) {
            return !(first == second);
        }

        /*/////////////// Arithmetic ///////////////*/
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

        /*/////////////// Assigment operators ///////////////*/
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
#pragma clang diagnostic pop