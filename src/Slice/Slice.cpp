#pragma once

#include "Slice.h"

namespace LinearAlgebra {

    Slice::Slice()
        : begin(Index()), end(Index()) {}

    Slice::Slice(Index begin, Index end)
        : begin(begin), end(end) {}

    Slice::Slice(int beginRow, int beginColumn, int endRow, int endColumn)
        :
        begin(Index(beginRow, beginColumn)),
        end(Index(endRow, endColumn)) {}


    Slice MakeSlice(Index begin, Index end){
        return Slice(begin, end);
    }
}