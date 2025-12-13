#include "npc.h"
#include "pegasus.h"
#include "dragon.h"
#include "knight.h"
#include "fight_io.h" 

set_t fight(const set_t &array, size_t distance)
{
    set_t dead_list;

    for (const auto &attacker : array)
        for (const auto &defender : array)
        {
            if ((attacker != defender) && (attacker->is_close(defender, distance)))
            {
                if (defender->accept(attacker))
                    dead_list.insert(defender);
            }
        }

    return dead_list;
}

int main()
{
    set_t array; 

    std::cout << "Generating ..." << std::endl;
    for (size_t i = 0; i < 100; ++i)
        array.insert(factory(NpcType(std::rand() % 3 + 1),
                             std::rand() % 100,
                             std::rand() % 100));
    
    std::cout << "Saving ..." << std::endl;
    save_to_file(array, "npc.txt");

    std::cout << "Loading ..." << std::endl;
    array = load_from_file("npc.txt");

    std::cout << "Fighting ..." << std::endl 
              << array; 

    for (size_t distance = 20; (distance <= 100) && !array.empty(); distance += 10)
    {
        auto dead_list = fight(array, distance);
        for (auto &d : dead_list)
            array.erase(d);
            
        std::cout << "Fight stats ----------" << std::endl
                  << "distance: " << distance << std::endl
                  << "killed: " << dead_list.size() << std::endl
                  << std::endl << std::endl;
    }

    std::cout << "Survivors:" << array;

    return 0;
}