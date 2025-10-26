#ifndef FIVE_H
#define FIVE_H

#include <string>

class Five {
private:
    unsigned char* digits;
    size_t size;
    
    int charToInt(unsigned char c) const;
    unsigned char intToChar(int n) const;
    Five createFromDigits(unsigned char* digits_array, size_t digits_size) const;
    
public:
    Five();
    Five(const char* fiveStr);
    Five(const Five& other);
    ~Five();
    
    size_t getSize() const;
    
    std::string toString() const;
    void print() const;
    
    int compare(const Five& other) const;
    bool equals(const Five& other) const;
    bool isGreater(const Five& other) const;
    bool isLess(const Five& other) const;
    
    Five add(const Five& other) const;
    Five subtract(const Five& other) const;
};

bool validChar(char c);

#endif