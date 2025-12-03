#pragma once

#include<string>
#include<memory>

#include<npc.hpp>

struct Knight : public NPC {
    Knight();
    Knight(const std::string& name_, int x_, int y_);
    ~Knight() noexcept;
};