#include <vector>
#include <ostream>

namespace LinearAlgebra {
    template<int rows, int columns, typename type = int>
    class Matrix {
    private:
        using MatrixType = Matrix<rows, columns, type>;

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
        void fill(const Matrix<rows, columns, type>& other);

        void print(std::ostream& stream);
        void print();

        type& at(int rowIndex, int columnIndex);
        const type& at(int rowIndex, int columnIndex) const;

        type& atSingleIndex(int index);
        const type& atSingleIndex(int index) const;

    public:
        // Constructors
        Matrix();
        Matrix(const MatrixType& other);
        Matrix(std::vector<type> other);

        // Destructor
        ~Matrix() = default;

        // Operators
        type& operator()(int rowIndex, int columnIndex);
        type& operator()(int index);

        const type& operator()(int rowIndex, int columnIndex) const;
        const type& operator()(int index) const;

        MatrixType operator+(const MatrixType& other);

    };

    class Vector {

    };
}