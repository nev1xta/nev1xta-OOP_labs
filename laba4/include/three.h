#pragma once

#include<initializer_list>
#include<stdexcept>

#include<figure.h>

template<class T> class Three : public Figure<T> {
public:
    Three();
    Three(const std::initializer_list<Point<T>>&);
    ~Three();
};

#include<Three.ipp>