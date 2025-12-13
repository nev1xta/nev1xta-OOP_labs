#pragma once

#include<iostream>

struct Point {
    int x, y;
    friend std::istream& operator>>(std::istream&, Point&);
    friend std::ostream& operator<<(std::ostream&, Point&);
    Point();
    Point(int, int);
    friend bool operator==(Point, Point);
    friend bool operator!=(Point, Point);
};
