#pragma once

#include <vector>
#include <ostream>
#include "Matrix/Slice/Slice.h"

namespace LinearAlgebra {
    template<typename type = int>
    class Matrix {
    private:
        using MatrixType = Matrix<type>;

    private: // Private members
        int rowCount;
        int columnCount;
        int capacity;
        std::vector<type> data;

    public: // Getters
        int getRowCount() const;

        int getColumnCount() const;

        int getCapacity() const;

    public: // Public methods
        void fill(const std::vector<type>& vector);
        void fill(const Matrix<type>& other);

        void print(std::ostream& stream);
        void print();

        type& at(int rowIndex, int columnIndex);
        const type& at(int rowIndex, int columnIndex) const;

        type& atSingleIndex(int index);
        const type& atSingleIndex(int index) const;

        std::vector<type> at(Slice slice);
        MatrixType at(Slice2d slice);

    public:
        // Constructors
        Matrix(int rowCount, int columnCount);
        Matrix(const MatrixType& other);
        Matrix(int rowCount, int columnCount, std::vector<type> other);

        // Destructor
        ~Matrix() = default;

        // Operators
        type& operator()(int rowIndex, int columnIndex);
        type& operator()(int index);

        const type& operator()(int rowIndex, int columnIndex) const;
        const type& operator()(int index) const;

        MatrixType operator+(const MatrixType& other);
        MatrixType operator*(const MatrixType& other);

    };
}