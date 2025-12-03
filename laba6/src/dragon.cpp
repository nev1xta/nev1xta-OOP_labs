#include<dragon.hpp>

Dragon::Dragon() : NPC() {
    type = DragonType;
}

Dragon::Dragon(const std::string& name_, int x_, int y_) : NPC(name_, x_, y_) {
    type = DragonType;
}

Dragon::~Dragon() noexcept = default;