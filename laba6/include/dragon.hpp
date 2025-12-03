#pragma once

#include<string>
#include<memory>

#include<npc.hpp>

struct Dragon : public NPC {
    Dragon();
    Dragon(const std::string& name_, int x_, int y_);
    ~Dragon() noexcept;
};