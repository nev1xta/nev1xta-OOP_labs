#include<vector_figure.h>
#include<figure.h>

VectorFigure::VectorFigure() : size(0), capacity(1), v(new Figure*[capacity]) {}

VectorFigure::VectorFigure(const VectorFigure& other)
    : size(other.size), capacity(other.capacity),
      v(new Figure*[capacity]) {
  std::copy(other.v, other.v + size, v);
}

VectorFigure::VectorFigure(VectorFigure&& other) noexcept
    : size(other.size), capacity(other.capacity), v(other.v) {
  other.clear();
}

VectorFigure::~VectorFigure() { delete[] v; }

void VectorFigure::resize(size_t newsize) {
  capacity = newsize;
  Figure** t = new Figure*[capacity];
  std::copy(v, v + size, t);
  delete[] v;
  v = t;
}

void VectorFigure::erase(size_t ind) {
  for (size_t i = ind; i < size; ++i) {
    v[i] = v[i + 1];
  }
  --size;
}

void VectorFigure::push(Figure* c) {
  if (size >= capacity) {
    resize(2 * capacity);
  }
  v[size++] = c;
}

void VectorFigure::pop() {
  if (size) {
    --size;
  }
}

Figure* VectorFigure::get(size_t i) { return v[i]; }

size_t VectorFigure::len() { return size; }

void VectorFigure::clear() {
  size = 0;
  capacity = 1;
  delete[] v;
  v = new Figure*[capacity];
}
