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
        int beginRow, int endRow,
        int beginColumn, int endColumn
    ) :
    beginRow(beginRow), endRow(endRow),
    beginColumn(beginColumn), endColumn(endColumn)
    {}
