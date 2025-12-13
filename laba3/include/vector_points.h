#pragma once

#include <iostream>
#include<point.h>

class VectorPoints {
private:
  size_t size;
  size_t capacity;
  Point* v;
public:
  void push(Point);
  void pop();
  void clear();
  void set(size_t, Point);
  void resize(size_t sz);

  Point get(size_t) const;

  size_t len() const;

  VectorPoints(VectorPoints&&) noexcept;
  VectorPoints(const VectorPoints&);
  VectorPoints();
  VectorPoints(size_t);
  ~VectorPoints();
};
