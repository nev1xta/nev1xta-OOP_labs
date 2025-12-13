#pragma once

#include<iostream>
#include<figure.h>

class Octagon : public Figure {
public:
    Octagon();
    ~Octagon();
    Octagon(Point, Point, Point, Point, Point, Point, Point, Point);

};
