#pragma once

#include <three.h>

template<class T>
Three<T>::Three() : Figure<T>(3) {}

template<class T>
Three<T>::Three(const std::initializer_list<Point<T>>& lst) : Figure<T>(lst) {
    if (lst.size() != 3) {
        throw std::invalid_argument("Three must have exactly 3 points");
    }
}

template<class T>
Three<T>::~Three() = default;