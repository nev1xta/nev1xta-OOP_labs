#include "npc.h"

NPC::NPC(NpcType t, int _x, int _y, const std::string &_name) : type(t), x(_x), y(_y), name(_name) {}

NPC::NPC(NpcType t, std::istream &is) : type(t)
{
    is >> name;
    is >> x;
    is >> y;
}

void NPC::subscribe(std::shared_ptr<IFightObserver> observer)
{
   observers.push_back(observer);
}

void NPC::fight_notify(const std::shared_ptr<NPC> defender, bool win)
{
    for (auto &o : observers)
        o->on_fight(shared_from_this(), defender, win);
}

bool NPC::is_close(const std::shared_ptr<NPC> &other, size_t distance) const
{
    auto dist = std::pow(x - other->x, 2) + std::pow(y - other->y, 2);
    return (dist <= std::pow(distance, 2));
}

void NPC::save(std::ostream &os)
{
    os << name << " " << x << " " << y << std::endl;
}

std::ostream &operator<<(std::ostream &os, NPC &npc)
{
    os << "{ " << npc.name << ": x:" << npc.x << ", y:" << npc.y << "} ";
    return os;
}