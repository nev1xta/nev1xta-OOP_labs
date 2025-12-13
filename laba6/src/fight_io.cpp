#include "fight_io.h"
#include <fstream>
#include <iostream>
#include <cstring>

std::shared_ptr<IFightObserver> TextObserver::get()
{
    static TextObserver instance;
    return std::shared_ptr<IFightObserver>(&instance, [](IFightObserver *) {});
}

void TextObserver::on_fight(const std::shared_ptr<NPC> attacker, const std::shared_ptr<NPC> defender, bool win)
{
    if (win)
    {
        std::cout << std::endl
                  << "Murder --------" << std::endl;
        attacker->print();
        defender->print();
    }
}


void save_to_file(const set_t &array, const std::string &filename)
{
    std::ofstream fs(filename);
    fs << array.size() << std::endl;
    for (auto &n : array)
        n->save(fs);
    fs.flush();
    fs.close();
}

set_t load_from_file(const std::string &filename)
{
    set_t result;
    std::ifstream is(filename);
    if (is.good() && is.is_open())
    {
        int count;
        is >> count;
        for (int i = 0; i < count; ++i)
            result.insert(factory(is)); 
        is.close();
    }
    else
        std::cerr << "Error: " << std::strerror(errno) << std::endl;
    return result;
}

std::ostream &operator<<(std::ostream &os, const set_t &array)
{
    for (auto &n : array)
        n->print();
    return os;
}