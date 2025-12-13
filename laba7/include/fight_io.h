#pragma once
#include "npc.h"
#include <memory>
#include <set>
#include <string>
#include <mutex>

extern std::mutex print_mutex; 

class TextObserver : public IFightObserver
{
private:
    TextObserver(){};

public:
    static std::shared_ptr<IFightObserver> get();
    void on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win) override;
};

void save_to_file(const set_t &array, const std::string &filename);
set_t load_from_file(const std::string &filename);

std::ostream &operator<<(std::ostream &os, const set_t &array);