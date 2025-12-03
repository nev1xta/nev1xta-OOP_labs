#include "Five.h"
#include <iostream>

int main() {
    // Простые тесты сложения
    std::cout << "=== Сложение ===" << std::endl;
    
    Five a("13");
    Five b("24");
    Five result1 = a.sum(b);
    std::cout << "13 + 24 = ";
    result1.print();  // Ожидается 42 (8 + 14 = 22 в десятичной, 22 = 4*5 + 2)
    
    Five c("10");
    Five d("10");
    Five result2 = c.sum(d);
    std::cout << "10 + 10 = ";
    result2.print();  // Ожидается 20 (5 + 5 = 10 в десятичной, 10 = 2*5 + 0)
    
    // Простые тесты вычитания
    std::cout << "\n=== Вычитание ===" << std::endl;
    
    Five e("32");
    Five f("14");
    Five result3 = e.sub(f);
    std::cout << "32 - 14 = ";
    result3.print();  // Ожидается 13 (17 - 9 = 8 в десятичной, 8 = 1*5 + 3)
    
    Five g("40");
    Five h("21");
    Five result4 = g.sub(h);
    std::cout << "40 - 21 = ";
    result4.print();  // Ожидается 14 (20 - 11 = 9 в десятичной, 9 = 1*5 + 4)
    
    // Тест с переносом
    std::cout << "\n=== Тест с переносом ===" << std::endl;
    
    Five i("44");
    Five j("11");
    Five result5 = i.sum(j);
    std::cout << "44 + 11 = ";
    result5.print();  // Ожидается 110 (24 + 6 = 30 в десятичной, 30 = 1*25 + 1*5 + 0)
    
    // Тест исключения
    std::cout << "\n=== Тест исключения ===" << std::endl;
    
    try {
        Five small("12");
        Five big("33");
        Five error = small.sub(big);
        std::cout << "ОШИБКА: исключение не сработало!" << std::endl;
    } catch (const std::underflow_error& e) {
        std::cout << "✓ Правильно поймано исключение: " << e.what() << std::endl;
    }
    
    return 0;
}