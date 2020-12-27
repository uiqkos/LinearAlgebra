#pragma once

namespace LinearAlgebra {
    class Slice {
    private:
        int begin;
        int end;

    public:
        int getBegin() const;
        int getEnd() const;

    public:
        Slice(int begin, int end);
    };

    class Slice2d {
    public:
        int beginRow;
        int endRow;

        int beginColumn;
        int endColumn;

    public:
        Slice2d(int beginRow, int endRow, int beginColumn, int endColumn);
    };
}