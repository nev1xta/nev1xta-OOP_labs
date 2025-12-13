#include "knight.h"
#include "dragon.h"
#include "pegasus.h"
#include <cstdlib> 

Knight::Knight(int x, int y, const std::string &_name) : NPC(KnightType, x, y, _name) {}
Knight::Knight(std::istream &is) : NPC(KnightType, is) {}

void Knight::print()
{
    std::cout << *this;
}

void Knight::save(std::ostream &os)
{
    os << "Knight ";
    NPC::save(os);
}

bool Knight::accept(std::shared_ptr<NPC> visitor)
{
    return visitor->fight(std::static_pointer_cast<Knight>(shared_from_this()));
}

bool Knight::fight(std::shared_ptr<Dragon> other)
{
    int attack = std::rand() % 6 + 1;
    int defense = std::rand() % 6 + 1;
    
    bool win = attack > defense;
    
    fight_notify(other, win);
    return win;
}

bool Knight::fight(std::shared_ptr<Knight> other)
{
    fight_notify(other, false);
    return false;
}

bool Knight::fight(std::shared_ptr<Pegasus> other)
{
    fight_notify(other, false);
    return false;
}

std::ostream &operator<<(std::ostream &os, Knight &knight)
{
    os << "knight: " << *static_cast<NPC *>(&knight) << std::endl;
    return os;
}