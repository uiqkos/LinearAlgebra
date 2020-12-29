#pragma once

class Index {
public:
    int row;
    int column;

public:
    Index();
    Index(int row, int column);

    Index operator+(const Index& other) const ;
    Index operator-(const Index& other) const ;
    Index operator*(const Index& other) const ;

};
