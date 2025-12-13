#include "Five.h"
#include <stdexcept>  
#include <iostream>
#include "customVector.h"

Five::Five(){
    data.push(0);
    
};


Five::Five(const std::string &num) {
    if (num.empty()) {
        data.push(0);
        return;
    }
    
    for (int i = num.length() - 1; i >= 0; i--) {
        char c = num[i] - '0';
        if(c < 0 || c > 4) {
            throw std::invalid_argument("invalid num");
        }
        data.push(c);
    }
}

Five::Five(const Five &o) : data(o.data) {}

Five::~Five() {}


size_t Five::size() const { return data.len(); }


Five Five::sum(const Five &o) const {
    Five res;
    size_t n = std::max(size(), o.size());

    int per = 0;//перенос
    for(size_t i = 0; i < n; i++) {
        int s = per;//сумма
        if (i < size()) {
            s += data.get(i);
        };
        if (i < o.size()) {
            s += o.data.get(i);
        };
        unsigned char digit = s % 5;
        per = s / 5;
        res.data.push(digit);
    }
    if (per > 0) {
        res.data.push(per);
    }
    return res;

}


Five Five::sub(const Five &o) const {

    if(this->lt(o)){
    throw std::underflow_error("neg res");
    }
    Five res;
    size_t n = std::max(size(), o.size());
    int per = 0;
    for (size_t i = 0; i < n; i++){
        int d = data.get(i) - per;
        if (i < o.size()) {
            d -= o.data.get(i);
        }

        if (d < 0) {
            d += 5;
            per = 1;
        } else {
            per = 0;
        }

        res.data.push(d);
    }
    return res;
}

bool Five::lt(const Five &o) const {
    if (size() != o.size()) {
        return size() < o.size();
    }
    for (int i = size() - 1; i >= 0; i--) {
        if (data.get(i) != o.data.get(i)) {
            return data.get(i) < o.data.get(i);
        }
    }
    return false;
}

bool Five::eq(const Five &o) const {
    if (size() != o.size()) {
        return false;
    }
    size_t n = size();
    for (size_t i = 0; i < n; i++) {
       
        if (data.get(i) != o.data.get(i)) {
            return false;
        }
    }

    return true;
}

bool Five::mt(const Five &o) const {
    if (size() != o.size()) {
         return size() > o.size();
    }
    size_t n = size();
    for (int i = n - 1; i >= 0; i--) {
        if (data.get(i)!= o.data.get(i)) {
        return data.get(i) > o.data.get(i);
        }
    }
     
     return false;
}

void Five::print() const {
    for (int i = size() - 1; i >= 0; i--) {
        std::cout << (int)data.get(i);
    }
    std::cout << std::endl;
}