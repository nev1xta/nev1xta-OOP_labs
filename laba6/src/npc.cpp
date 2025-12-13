#include "npc.h"
#include "dragon.h"
#include "knight.h"
#include "pegasus.h"
#include "fight_io.h" // Для TextObserver
#include <cmath>

// -----------------------------------------------------------------------
// NPC Implementation
// -----------------------------------------------------------------------

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

bool NPC::is_close(const std::shared_ptr<NPC> &other) const
{
    auto dist_sq = std::pow(x - other->x, 2) + std::pow(y - other->y, 2);
    // Берем радиус атаки у ТЕКУЩЕГО объекта (атакующего)
    int range = get_fight_range(); 
    return (dist_sq <= std::pow(range, 2));
}

void NPC::move(int shift_x, int shift_y, int max_x, int max_y)
{
    std::lock_guard<std::mutex> lck(mtx);
    if ((x + shift_x >= 0) && (x + shift_x < max_x))
        x += shift_x;
    if ((y + shift_y >= 0) && (y + shift_y < max_y))
        y += shift_y;
}

bool NPC::is_alive() const
{
    // Можно добавить mutex, если нужна строгая синхронизация чтения
    return alive;
}

void NPC::must_die()
{
    std::lock_guard<std::mutex> lck(mtx);
    alive = false;
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

// -----------------------------------------------------------------------
// Factory Implementation (Должна быть только один раз!)
// -----------------------------------------------------------------------

std::shared_ptr<NPC> factory(std::istream &is)
{
    std::shared_ptr<NPC> result;
    std::string type;
    if (is >> type)
    {
        if (type == "Pegasus") result = std::make_shared<Pegasus>(is);
        else if (type == "Dragon") result = std::make_shared<Dragon>(is);
        else if (type == "Knight") result = std::make_shared<Knight>(is);
        else std::cerr << "unexpected NPC type: " << type << std::endl;
    }

    if (result)
        result->subscribe(TextObserver::get());

    return result;
}

std::shared_ptr<NPC> factory(NpcType type, int x, int y)
{
    std::shared_ptr<NPC> result;
    std::string name;
    
    // Генерация случайного имени
    switch (type) {
        case PegasusType: name = "Pegasus_" + std::to_string(std::rand() % 100); break;
        case DragonType: name = "Dragon_" + std::to_string(std::rand() % 100); break;
        case KnightType: name = "Knight_" + std::to_string(std::rand() % 100); break;
        default: name = "Unknown"; break;
    }

    switch (type)
    {
    case PegasusType:
        result = std::make_shared<Pegasus>(x, y, name);
        break;
    case DragonType:
        result = std::make_shared<Dragon>(x, y, name);
        break;
    case KnightType:
        result = std::make_shared<Knight>(x, y, name);
        break;
    default:
        break;
    }
    
    if (result)
        result->subscribe(TextObserver::get());

    return result;
}