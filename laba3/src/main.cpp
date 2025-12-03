#include<iostream>
#include<figure.h>
#include<octagon.h>
#include<pentagon.h>
#include<hexagon.h>
#include<vector_figure.h>
int main() {
    VectorFigure v;
    std::cout << "INPUT VECTOR SIZE ";
    int n;
    std::cin >> n;
    std::cout << "1-Octagon\n2-Pentagon\n3-Hexagon\n";
    for (int i = 0; i < n; ++i) {
        char c;
        std::cin >> c;
        Figure* f;
        if (c == '1') {
            f = new Octagon();
        } else if (c == '2') {
            f = new Pentagon();
        } else if (c == '3') {
            f = new Hexagon();
        } else {
            std::cout << std::endl;
        }
        std::cin >> *f;
        v.push(f);
    }
    std::cout << "Do you want to erase the shape? Y/N\n";
    char q;
    std::cin >> q;
    if (q == 'Y') {
        std::cout << "INPUT ERASE INDEX\n";
        size_t ind;
        std::cin >> ind;
        v.erase(ind);
        std::cout << v.len() << std::endl;
    }
    for (size_t i = 0; i < v.len(); ++i) {
        std::cout << v.get(i)->Area() << std::endl;
    }
    return 0;
}
