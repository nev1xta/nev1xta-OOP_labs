#pragma once

#include<iostream>
#include<figure.h>

class Pentagon : public Figure {
public:
    Pentagon();
    ~Pentagon();
    Pentagon(Point, Point, Point, Point, Point);
};
