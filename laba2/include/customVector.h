#pragma once
#include <iostream>

class CustomVector {
private:
  size_t size;
  size_t capacity;
  unsigned char *v;
  void resize(size_t sz);

public:
  void push(unsigned char);
  void pop();

  unsigned char get(size_t) const;

  size_t len() const;

  CustomVector(const CustomVector &);
  CustomVector();
  ~CustomVector();
};