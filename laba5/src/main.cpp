#include<iostream>

#include"queue.hpp"

int main() {
    Queue<int> q{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for (const auto& i : q) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    return 0;
}