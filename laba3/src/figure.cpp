#include<figure.h>

Figure::Figure() {}

long double Figure::CalcArea(const VectorPoints& t) const {
    long double res{0.0};
    for (int i = 0; i + 1 < t.len(); ++i) {
        res += (long long)t.get(i).x * (long long)t.get(i + 1).y;
        res -= (long long)t.get(i + 1).x * (long long)t.get(i).y;
    }
    res += (long long)t.get(t.len() - 1).x * (long long)t.get(0).y;
    res -= (long long)t.get(0).x * (long long)t.get(t.len() - 1).y;
    return std::abs(res / 2.0);
}

long double Figure::Area() { return CalcArea(v); }

Point Figure::CalcCentr(const VectorPoints& t) const {
    int x = 0, y = 0;
    for (int i = 0; i < t.len(); ++i) {
        x += t.get(i).x;
        y += t.get(i).y;
    }
    return Point(x / t.len(), y / t.len());
}

void Figure::ReadPoints(std::istream& is) {
    for (size_t i = 0; i < v.len(); ++i) {
        Point p;
        is >> p.x >> p.y;
        v.set(i, p);
    }
}

void Figure::PrintPoints(std::ostream& os) {
    for (size_t i = 0; i < v.len(); ++i) {
        Point p = v.get(i);
        os << "( " << p.x << ", " << p.y << ")";
    }
}

std::istream& operator>>(std::istream& is, Figure& f) {
    f.ReadPoints(is);
    return is;
}

std::ostream& operator<<(std::ostream& os, Figure& f) {
    f.PrintPoints(os);
    return os;
}

bool operator==(Figure a, Figure b) {
  if (a.v.len() != b.v.len()) {
    return false;
  }
  for (int i = 0; i < a.v.len(); ++i) {
    if (a.v.get(i) != b.v.get(i)) {
      return false;
    }
  }
  return true;
}

bool operator!=(Figure a, Figure b) { return !(a == b); }

Figure::~Figure() {}