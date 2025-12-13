#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <set>
#include <string>
#include <math.h>
#include <mutex> // Важно для std::mutex

struct NPC;
struct Dragon;
struct Knight;
struct Pegasus;

using set_t = std::set<std::shared_ptr<NPC>>;

enum NpcType
{
    Unknown = 0,
    DragonType = 1,
    KnightType = 2,
    PegasusType = 3
};

struct IFightObserver{
    virtual void on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) = 0;
};

struct NPC : public std::enable_shared_from_this<NPC>
{
    NpcType type;
    int x{0};
    int y{0};
    std::string name;
    std::vector<std::shared_ptr<IFightObserver>> observers;
    
    // Новые поля для многопоточности
    bool alive{true};
    mutable std::mutex mtx; // Мьютекс для защиты полей конкретного NPC

    NPC(NpcType t, int _x, int _y, const std::string &_name);
    NPC(NpcType t, std::istream &is);

    void subscribe(std::shared_ptr<IFightObserver> observer);
    void fight_notify(const std::shared_ptr<NPC> defender, bool win);
    
    // Проверка дистанции (зависит от типа атакующего)
    virtual bool is_close(const std::shared_ptr<NPC> &other) const;
    virtual int get_fight_range() const { return 0; } // Дистанция атаки по умолчанию

    // Движение и жизнь
    virtual void move(int shift_x, int shift_y, int max_x, int max_y);
    bool is_alive() const;
    void must_die();

    // Visitor
    virtual bool accept(std::shared_ptr<NPC> visitor) = 0;

    // Visitors
    virtual bool fight(std::shared_ptr<Dragon> other) = 0;
    virtual bool fight(std::shared_ptr<Knight> other) = 0;
    virtual bool fight(std::shared_ptr<Pegasus> other) = 0;

    virtual void print() = 0;
    virtual void save(std::ostream &os);

    friend std::ostream &operator<<(std::ostream &os, NPC &npc);
};

std::shared_ptr<NPC> factory(std::istream &is);
std::shared_ptr<NPC> factory(NpcType type, int x, int y);