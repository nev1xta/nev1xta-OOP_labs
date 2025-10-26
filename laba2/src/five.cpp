#include "../include/five.h"
#include <iostream>
#include <string>
#include <cstring>


// support function
size_t Five::getSize() const {
    return size;
}

bool validChar(char c) {
    return (c >= '0' && c <= '4');
}

int Five::charToInt(unsigned char c) const {
    if (c >= '0' && c <= '4') return c - '0';
    throw std::invalid_argument("Invalid character for base 5");
}

unsigned char Five::intToChar(int n) const {
    if (n < 0 || n > 4) throw std::invalid_argument("Invalid value for base 5");
    return '0' + n;
}

Five Five::createFromDigits(unsigned char* digits_array, size_t digits_size) const {
    Five result;
    
    result.digits = new unsigned char[digits_size];
    result.size = digits_size;
    
    for (size_t i = 0; i < digits_size; i++) {
        result.digits[i] = digits_array[i];
    }
    
    return result;
}


// CONSTRUCTORS AND DESTRUCTOR
Five::Five() : digits(nullptr), size(0) {}

Five::Five(const char* fiveStr) {
    if (fiveStr == nullptr || fiveStr[0] == '\0') {
        throw std::invalid_argument("Empty string");
    }
    
    for (int i = 0; fiveStr[i] != '\0'; i++) {
        if (!validChar(fiveStr[i])) {
            throw std::invalid_argument("Invalid characters for base 5");
        }
    }

    size = strlen(fiveStr);
    digits = new unsigned char[size];
    for (int i = 0; i < size; i++) {
        digits[i] = fiveStr[size - 1 - i];
    }
}

Five::Five(const Five& other) {
    size = other.size;
    digits = new unsigned char[size];
    for (int i = 0; i < size; i++) {
        digits[i] = other.digits[i];
    }
}

Five::~Five() {
    delete[] digits;
    digits = nullptr;
    size = 0;
}


//       basic functionality
std::string Five::toString() const {
    if (size == 0 || digits == nullptr) {
        return "0";
    }
    
    std::string result;
    
    for (int i = size - 1; i >= 0; i--) {
        result += digits[i];
    }
    
    return result;
}

void Five::print() const {
    std::cout << this->toString() << std::endl;
}

int Five::compare(const Five& other) const {
    if (size != other.size) {
        return (size > other.size) ? 1 : -1;
    }
    for (int i = size - 1; i >= 0; i--) {
        int digit1 = charToInt(digits[i]);
        int digit2 = charToInt(other.digits[i]);
        if (digit1 != digit2) {
            return (digit1 > digit2) ? 1 : -1;
        }
    }
    return 0;
}

bool Five::equals(const Five& other) const {
    return compare(other) == 0;
}

bool Five::isGreater(const Five& other) const {
    return compare(other) > 0;
}

bool Five::isLess(const Five& other) const {
    return compare(other) < 0;
}

Five Five::add(const Five& other) const {
    size_t max_size = (size > other.size) ? size : other.size;
    max_size += 1;
    
    unsigned char* result_digits = new unsigned char[max_size];
    size_t result_size = 0;
    
    int i = 0;
    int carry = 0;
    
    while (i < size || i < other.size || carry > 0) {
        int digit1 = (i < size) ? charToInt(digits[i]) : 0;
        int digit2 = (i < other.size) ? charToInt(other.digits[i]) : 0;
        int sum = digit1 + digit2 + carry;
        
        carry = sum / 5;  
        int resDigit = sum % 5; 
        
        result_digits[result_size] = intToChar(resDigit);
        result_size++;
        i++;
    }
    Five result = createFromDigits(result_digits, result_size);
    delete[] result_digits;
    
    return result;
}

Five Five::subtract(const Five& other) const {
    if (this->compare(other) < 0) {
        throw std::underflow_error("Negative result");
    }
    unsigned char* result_digits = new unsigned char[size];
    size_t result_size = 0;
    
    int carry = 0;
    int i = 0;

    while (i < size) {
        int digit1 = charToInt(digits[i]);
        int digit2 = (i < other.size) ? charToInt(other.digits[i]) : 0;

        digit1 -= carry;
        carry = 0;

        if (digit1 < digit2) {
            digit1 += 5;  
            carry = 1;
        }
        
        int diff = digit1 - digit2;
        result_digits[result_size] = intToChar(diff);
        result_size++;
        i++;
    }

    while (result_size > 1 && result_digits[result_size - 1] == '0') {
        result_size--;
    }
    
    Five result = createFromDigits(result_digits, result_size);
    delete[] result_digits;
    
    return result;
}