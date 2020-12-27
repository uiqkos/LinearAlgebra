#pragma once

#include <vector>
#include <ostream>
#include "Matrix/Slice/Slice.h"
#include "Utils/Utils.cpp"

namespace LinearAlgebra {
    template<typename type = int>
    class Matrix {
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
        Matrix<type> at(Slice2d slice);

    public:
        // Constructors
        Matrix(int rowCount, int columnCount);
        Matrix(const Matrix<type>& other);
        Matrix(int rowCount, int columnCount, std::vector<type> other);

        // Destructor
        ~Matrix() = default;

        // Operators
        type& operator()(int rowIndex, int columnIndex);
        type& operator()(int index);

        const type& operator()(int rowIndex, int columnIndex) const;
        const type& operator()(int index) const;

        Matrix<type> operator+(const Matrix<type>& other);
        Matrix<type> operator+(const type& constant);

        // TODO: delete this shit
        Matrix<type> smatrix(const type& constant);
        Matrix<type> svector(const type& constant);


        Matrix<type> operator*(const Matrix<type>& other);
        Matrix<type> operator*(const type& constant);

    };
}