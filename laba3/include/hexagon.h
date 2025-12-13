#pragma once

#include<iostream>
#include<figure.h>

class Hexagon : public Figure {
public:
    Hexagon();
    ~Hexagon();
    Hexagon(Point, Point, Point, Point, Point, Point);

};
