#pragma once
#include "npc.h"

struct Dragon : public NPC
{
    Dragon(int x, int y, const std::string &_name);
    Dragon(std::istream &is);

    void print() override;
    void save(std::ostream &os) override;
    bool accept(std::shared_ptr<NPC> visitor) override;

    bool fight(std::shared_ptr<Pegasus> other) override;
    bool fight(std::shared_ptr<Dragon> other) override;
    bool fight(std::shared_ptr<Knight> other) override;

    friend std::ostream &operator<<(std::ostream &os, Dragon &dragon);
};