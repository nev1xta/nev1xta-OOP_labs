#include "npc.h"
#include "dragon.h"
#include "knight.h"
#include "pegasus.h"
#include "fight_io.h"

#include <chrono>
#include <thread>
#include <mutex>
#include <atomic>
#include <vector>
#include <algorithm>
#include <coroutine>
#include <random>    

using namespace std::chrono_literals;

std::mutex game_mtx;
set_t array_npcs;    
std::atomic<bool> run_game{true}; 

struct FightRequest {
    struct promise_type;
    using handle_type = std::coroutine_handle<promise_type>;

    struct promise_type {
        std::pair<std::shared_ptr<NPC>, std::shared_ptr<NPC>> current_pair;

        FightRequest get_return_object() { 
            return FightRequest(handle_type::from_promise(*this)); 
        }
        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        
        std::suspend_always yield_value(std::pair<std::shared_ptr<NPC>, std::shared_ptr<NPC>> p) {
            current_pair = p;
            return {};
        }
        
        void return_void() {}
        void unhandled_exception() { std::terminate(); }
    };

    handle_type h;

    FightRequest(handle_type h) : h(h) {}
    ~FightRequest() { if (h) h.destroy(); }
    
    FightRequest(const FightRequest&) = delete;
    FightRequest& operator=(const FightRequest&) = delete;
    
    FightRequest(FightRequest&& other) noexcept : h(other.h) { other.h = nullptr; }
};

FightRequest run_fight_search() {
    while (run_game) {
        {
            std::lock_guard<std::mutex> lck(game_mtx);
            for (auto &npc : array_npcs) {
                if (!npc->is_alive()) continue;

                int move_dist = 0;
                if (npc->type == PegasusType) move_dist = 30;
                else if (npc->type == KnightType) move_dist = 30;
                else if (npc->type == DragonType) move_dist = 50;

                int dx = (std::rand() % (move_dist * 2 + 1)) - move_dist;
                int dy = (std::rand() % (move_dist * 2 + 1)) - move_dist;
                npc->move(dx, dy, 100, 100);
            }
        }

        std::vector<std::shared_ptr<NPC>> alive_npcs;
        {
             std::lock_guard<std::mutex> lck(game_mtx);
             for(auto& n : array_npcs) {
                 if(n->is_alive()) alive_npcs.push_back(n);
             }
        }

        for (auto &attacker : alive_npcs) {
            for (auto &defender : alive_npcs) {
                if (attacker != defender) {
                    if (attacker->is_close(defender)) {
                        co_yield std::make_pair(attacker, defender);
                    }
                }
            }
        }

        std::this_thread::sleep_for(10ms);
    }
}

void game_thread_func() {
    auto generator = run_fight_search();
    
    generator.h.resume();

    while (run_game && !generator.h.done()) {
        auto pair = generator.h.promise().current_pair;
        auto attacker = pair.first;
        auto defender = pair.second;

        if (attacker && defender && attacker->is_alive() && defender->is_alive()) {
            bool success = defender->accept(attacker);
            if (success) {
                defender->must_die();
            }
        }

        generator.h.resume();
    }
}

void print_map_thread() {
    while (run_game) {
        std::vector<std::string> map(100, std::string(100, ' '));

        {
            std::lock_guard<std::mutex> lck(game_mtx);
            for (const auto& npc : array_npcs) {
                if (npc->is_alive()) {
                    int x = std::clamp(npc->x, 0, 99);
                    int y = std::clamp(npc->y, 0, 99);
                    
                    char symbol = '.';
                    switch(npc->type) {
                        case DragonType: symbol = 'D'; break;
                        case KnightType: symbol = 'K'; break;
                        case PegasusType: symbol = 'P'; break;
                    }
                    map[y][x] = symbol;
                }
            }
        }

        {
            std::lock_guard<std::mutex> lck(print_mutex);
            
            std::cout << "\033[2J\033[1;1H"; 
            std::cout << "Map Snapshot:" << std::endl;
            
            for(int i=0; i<102; ++i) std::cout << "-";
            std::cout << std::endl;

            for (int i = 0; i < 100; ++i) {
                std::cout << "|"; 
                for (int j = 0; j < 100; ++j) {
                     std::cout << map[i][j];
                }
                std::cout << "|" << std::endl; 
            }
            
            for(int i=0; i<102; ++i) std::cout << "-";
            std::cout << std::endl;
        }

        std::this_thread::sleep_for(1s);
    }
}

int main()
{
    std::srand(std::time(nullptr));

    std::cout << "Generating 50 NPCs..." << std::endl;
    for (size_t i = 0; i < 50; ++i)
        array_npcs.insert(factory(NpcType(std::rand() % 3 + 1),
                             std::rand() % 100,
                             std::rand() % 100));

    std::thread logic_thread(game_thread_func);
    std::thread render_thread(print_map_thread);

    std::this_thread::sleep_for(30s);
    run_game = false;

    if (logic_thread.joinable()) logic_thread.join();
    if (render_thread.joinable()) render_thread.join();

    {
        std::lock_guard<std::mutex> lck(print_mutex);
        std::cout << "\nGame Over!" << std::endl;
        std::cout << "Survivors:" << std::endl;
        for (const auto& npc : array_npcs) {
            if (npc->is_alive()) {
                npc->print();
            }
        }
    }

    return 0;
}