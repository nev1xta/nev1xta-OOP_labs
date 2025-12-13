#pragma once
#include "npc.h"

struct Pegasus : public NPC
{
    Pegasus(int x, int y, const std::string &_name);
    Pegasus(std::istream &is);

    void print() override;
    void save(std::ostream &os) override;
    bool accept(std::shared_ptr<NPC> visitor) override;

    int get_fight_range() const override { return 10; }

    bool fight(std::shared_ptr<Pegasus> other) override;
    bool fight(std::shared_ptr<Dragon> other) override;
    bool fight(std::shared_ptr<Knight> other) override;

    friend std::ostream &operator<<(std::ostream &os, Pegasus &pegasus);
};