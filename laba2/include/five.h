#include <cstddef>
#include <string>
#include "customVector.h"

class Five {
    private:
        CustomVector data;
    public:
        Five();
        Five(const std::string &num);
        Five(std::initializer_list<unsigned char> list);


        ~Five();
        Five(const Five &o);
        Five(Five&& o) noexcept;

        Five sum(const Five &o) const;
        Five sub(const Five &o) const;
        bool lt(const Five &o) const;
        bool eq(const Five &o) const;
        bool mt(const Five &o) const;

        size_t size() const;
        void print() const;
};

