#pragma once

#include "Slice.h"
using namespace LinearAlgebra;


int Slice::getBegin() const {
    return begin;
}

int Slice::getEnd() const {
    return end;
}

Slice::Slice(int begin, int end)
    : begin(begin), end(end)
{}

Slice2d::Slice2d(
        int beginRow, int beginColumn,
        int endRow, int endColumn
    ) :
    beginRow(beginRow), beginColumn(beginColumn),
    endRow(endRow), endColumn(endColumn)
    {}
