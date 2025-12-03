#pragma once

#include<string>
#include<memory>

#include<npc.hpp>

struct Pegasus : public NPC {
    Pegasus();
    Pegasus(const std::string& name_, int x_, int y_);
    ~Pegasus() noexcept;
};