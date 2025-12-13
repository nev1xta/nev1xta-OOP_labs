#include "knight.h"
#include "pegasus.h"
#include "dragon.h"

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

bool Knight::fight(std::shared_ptr<Pegasus> other)
{
    fight_notify(other, true);
    return true;
}

bool Knight::fight(std::shared_ptr<Dragon> other)
{
    fight_notify(other, true);
    return true;
}

bool Knight::fight(std::shared_ptr<Knight> other)
{
    fight_notify(other, true);
    return true;
}

std::ostream &operator<<(std::ostream &os, Knight &dragon)
{
    os << "knight: " << *static_cast<NPC *>(&dragon) << std::endl;
    return os;
}