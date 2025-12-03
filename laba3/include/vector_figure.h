#pragma once

#include <iostream>
#include<figure.h>

class VectorFigure {
private:
  size_t size;
  size_t capacity;
  Figure** v;
  void resize(size_t sz);
public:
  void push(Figure*);
  void pop();
  void clear();
  void erase(size_t);

  Figure* get(size_t);
  
  size_t len();

  VectorFigure(VectorFigure&&) noexcept;
  VectorFigure(const VectorFigure&);
  VectorFigure();
  ~VectorFigure();
};
