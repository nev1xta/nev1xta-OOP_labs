#include<octagon.h>

Octagon::Octagon() {
    for (int i = 0; i < 8; ++i) {
        v.push(Point(0, 0));
    }
}

Octagon::Octagon(Point p1, Point p2, Point p3, Point p4, Point p5, Point p6, Point p7, Point p8) {
    v.push(p1);
    v.push(p2);
    v.push(p3);
    v.push(p4);
    v.push(p5);
    v.push(p6);
    v.push(p7);
    v.push(p8);
}

Octagon::~Octagon() {}