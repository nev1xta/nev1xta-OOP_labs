#pragma once

#include<iostream>
#include<vector_points.h>

class Figure {
public:
    Figure();
    virtual ~Figure();
    void ReadPoints(std::istream&);
    void PrintPoints(std::ostream&);
    virtual long double Area();
    friend bool operator==(Figure, Figure);
    friend bool operator!=(Figure, Figure);
protected:
    VectorPoints v;
    long double CalcArea(const VectorPoints&) const;
    Point CalcCentr(const VectorPoints&) const;
};
std::istream& operator>>(std::istream&, Figure&);
std::ostream& operator<<(std::ostream&, Figure&);
