#include "include/Five.h"
#include "iostream"

int main() {
    Five a("123");
    Five b(a);
    Five c("321");
    if (c.isGreater(a)){
        std::cout << b.toString() << std::endl;
        std::cout << a.compare(b) << std::endl;
    }
    return 0;
}