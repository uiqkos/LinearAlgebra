#pragma once
#include "Index/Index.h"

namespace LinearAlgebra {
    class Slice {
    public:
        Index begin;
        Index end;

    public:
        Slice();
        Slice(Index begin, Index end);
        Slice(int beginRow, int beginColumn, int endRow, int endColumn);
    };
}