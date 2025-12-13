#include "pegasus.h"
#include "dragon.h"
#include "knight.h"
#include <cstdlib> // Для std::rand()

Pegasus::Pegasus(int x, int y, const std::string &_name) : NPC(PegasusType, x, y, _name) {}
Pegasus::Pegasus(std::istream &is) : NPC(PegasusType, is) {}

void Pegasus::print()
{
    std::cout << *this;
}

void Pegasus::save(std::ostream &os)
{
    os << "Pegasus "; // Важно для фабрики
    NPC::save(os);
}

bool Pegasus::accept(std::shared_ptr<NPC> visitor) 
{
    // Я (Пегас) принимаю посетителя
    return visitor->fight(std::static_pointer_cast<Pegasus>(shared_from_this()));
}

// Пегас никого не атакует
bool Pegasus::fight(std::shared_ptr<Dragon> other)
{
    fight_notify(other, false);
    return false;
}

bool Pegasus::fight(std::shared_ptr<Knight> other)
{
    fight_notify(other, false);
    return false;
}

bool Pegasus::fight(std::shared_ptr<Pegasus> other)
{
    fight_notify(other, false);
    return false;
}

std::ostream &operator<<(std::ostream &os, Pegasus &pegasus)
{
    os << "pegasus: " << *static_cast<NPC *>(&pegasus) << std::endl;
    return os;
}