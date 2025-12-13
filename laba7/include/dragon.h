#pragma once
#include "npc.h"

struct Dragon : public NPC
{
    Dragon(int x, int y, const std::string &_name);
    Dragon(std::istream &is);

    void print() override;
    void save(std::ostream &os) override;
    bool accept(std::shared_ptr<NPC> visitor) override;
    
    // Дистанция атаки дракона 30
    int get_fight_range() const override { return 30; }

    bool fight(std::shared_ptr<Dragon> other) override;
    bool fight(std::shared_ptr<Knight> other) override;
    bool fight(std::shared_ptr<Pegasus> other) override;

    friend std::ostream &operator<<(std::ostream &os, Dragon &dragon);
};