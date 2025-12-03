#include<hexagon.h>

Hexagon::Hexagon() {
    for (int i = 0; i < 6; ++i) {
        v.push(Point(0, 0));
    }
}

Hexagon::Hexagon(Point p1, Point p2, Point p3, Point p4, Point p5, Point p6) {
    v.push(p1);
    v.push(p2);
    v.push(p3);
    v.push(p4);
    v.push(p5);
    v.push(p6);
}


Hexagon::~Hexagon() {}