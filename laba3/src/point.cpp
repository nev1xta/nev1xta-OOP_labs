#include<point.h>
#include<iostream>
#include<cmath>

std::istream& operator>>(std::istream& is, Point& p) {
  is >> p.x >> p.y;
  return is;
}

std::ostream& operator<<(std::ostream& os, Point& p) {
  os << '(' << p.x << ' ' << p.y << ')';
  return os;
}

Point::Point() : x(0), y(0) {}

Point::Point(int x_, int y_) : x(x_), y(y_) {}

bool operator==(Point a, Point b) { return a.x == b.x && a.y == b.y; }

bool operator!=(Point a, Point b) { return !(a == b); }