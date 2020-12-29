#pragma once

#include "Index.h"


Index::Index()
    : row(0), column(0)
{}

Index::Index(int row, int column)
    : row(row), column(column)
{}

Index Index::operator+(const Index& other) const {
    return Index(row + other.row, column + other.column);
}

Index Index::operator*(const Index& other) const {
    return Index(row * other.row, column * other.column);
}

Index Index::operator-(const Index& other) const {
    return Index(row - other.row, column - other.column);
}



