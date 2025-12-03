#include "customVector.h"

CustomVector::CustomVector() : size(0), capacity(1), v(new unsigned char[capacity]) {}

CustomVector::CustomVector(const CustomVector &other)
    : size(other.size), capacity(other.capacity),
      v(new unsigned char[capacity]) {
  std::copy(other.v, other.v + size, v);
}

CustomVector::~CustomVector() { delete[] v; }

void CustomVector::resize(size_t newsize) {
  capacity = newsize;
  unsigned char *t = new unsigned char[capacity];
  std::copy(v, v + size, t);
  delete[] v;
  v = t;
}

void CustomVector::push(unsigned char c) {
  if (size >= capacity) {
    resize(2 * capacity);
  }
  v[size++] = c;
}

void CustomVector::pop() {
  if (size) {
    --size;
  }
}

unsigned char CustomVector::get(size_t i) const { return v[i]; }

size_t CustomVector::len() const { return size; }
