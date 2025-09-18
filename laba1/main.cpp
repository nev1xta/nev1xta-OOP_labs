#include <iostream>
#include "include/def.h"

int main() {
    int devider, bound, res;
    std::cout << "Введите 2 целых числа через пробел. Делитель (!= 0) и границу (> 0)" << std::endl;
    std::cin >> devider >> bound;
    res = SearchN(devider, bound);
    std::cout << res << std::endl;
    return 0;
    } 