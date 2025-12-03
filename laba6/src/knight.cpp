#include<knight.hpp>

Knight::Knight() : NPC() {
    type = KnightType;
}

Knight::Knight(const std::string& name_, int x_, int y_) : NPC(name_, x_, y_) {
    type = KnightType;
}

Knight::~Knight() noexcept = default;