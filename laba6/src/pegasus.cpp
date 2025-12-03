#include<pegasus.hpp>

Pegasus::Pegasus() : NPC() {
    type = PegasusType;
}

Pegasus::Pegasus(const std::string& name_, int x_, int y_) : NPC(name_, x_, y_) {
    type = PegasusType;
}

Pegasus::~Pegasus() noexcept = default;