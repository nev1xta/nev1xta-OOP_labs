#include "dragon.h"
#include "knight.h"
#include "pegasus.h"
#include <cstdlib>

Dragon::Dragon(int x, int y, const std::string &_name) : NPC(DragonType, x, y, _name) {}
Dragon::Dragon(std::istream &is) : NPC(DragonType, is) {}

void Dragon::print() { std::cout << *this; }

void Dragon::save(std::ostream &os) {
    os << "Dragon ";
    NPC::save(os);
}

bool Dragon::accept(std::shared_ptr<NPC> visitor) {
    return visitor->fight(std::static_pointer_cast<Dragon>(shared_from_this()));
}

// Дракон -> Дракон (Нет)
bool Dragon::fight(std::shared_ptr<Dragon> other) {
    fight_notify(other, false);
    return false;
}

// Дракон -> Рыцарь (Нет по правилам K->D->P)
bool Dragon::fight(std::shared_ptr<Knight> other) {
    fight_notify(other, false);
    return false;
}

// Дракон -> Пегас (Да)
bool Dragon::fight(std::shared_ptr<Pegasus> other) {
    int attack = std::rand() % 6 + 1;
    int defense = std::rand() % 6 + 1;
    bool win = attack > defense;
    fight_notify(other, win);
    return win;
}

std::ostream &operator<<(std::ostream &os, Dragon &dragon) {
    os << "dragon: " << *static_cast<NPC *>(&dragon) << std::endl;
    return os;
}