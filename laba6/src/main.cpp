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
#include <algorithm> // Для std::clamp
#include <coroutine> // ОБЯЗАТЕЛЬНО для std::coroutine_handle
#include <random>    // Для std::rand

using namespace std::chrono_literals;

// Глобальные переменные
std::mutex game_mtx; // Мьютекс для защиты данных NPC
set_t array_npcs;    // Список всех NPC
std::atomic<bool> run_game{true}; // Флаг работы игры

// --------------------------------------------------------------------
// Инфраструктура Корутин (Generator)
// --------------------------------------------------------------------
struct FightRequest {
    struct promise_type;
    using handle_type = std::coroutine_handle<promise_type>;

    struct promise_type {
        // Храним пару, которую нашли
        std::pair<std::shared_ptr<NPC>, std::shared_ptr<NPC>> current_pair;

        FightRequest get_return_object() { 
            return FightRequest(handle_type::from_promise(*this)); 
        }
        std::suspend_always initial_suspend() { return {}; } // Не запускать сразу при создании
        std::suspend_always final_suspend() noexcept { return {}; }
        
        // Метод для co_yield
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
    
    // Запрещаем копирование, чтобы не разрушить хендл дважды
    FightRequest(const FightRequest&) = delete;
    FightRequest& operator=(const FightRequest&) = delete;
    
    // Разрешаем перемещение
    FightRequest(FightRequest&& other) noexcept : h(other.h) { other.h = nullptr; }
};

// --------------------------------------------------------------------
// Логика игры (Корутина)
// --------------------------------------------------------------------
FightRequest run_fight_search() {
    while (run_game) {
        // 1. Фаза движения
        {
            std::lock_guard<std::mutex> lck(game_mtx);
            for (auto &npc : array_npcs) {
                if (!npc->is_alive()) continue;

                int move_dist = 0;
                if (npc->type == PegasusType) move_dist = 30;
                else if (npc->type == KnightType) move_dist = 30;
                else if (npc->type == DragonType) move_dist = 50;

                // Случайное смещение
                int dx = (std::rand() % (move_dist * 2 + 1)) - move_dist;
                int dy = (std::rand() % (move_dist * 2 + 1)) - move_dist;
                npc->move(dx, dy, 100, 100);
            }
        }

        // 2. Фаза поиска битв
        // Создаем копию списка живых, чтобы не держать мьютекс слишком долго
        std::vector<std::shared_ptr<NPC>> alive_npcs;
        {
             std::lock_guard<std::mutex> lck(game_mtx);
             for(auto& n : array_npcs) {
                 if(n->is_alive()) alive_npcs.push_back(n);
             }
        }

        // Ищем пары
        for (auto &attacker : alive_npcs) {
            for (auto &defender : alive_npcs) {
                if (attacker != defender) {
                    if (attacker->is_close(defender)) {
                        // ПРИОСТАНАВЛИВАЕМ выполнение и возвращаем пару
                        co_yield std::make_pair(attacker, defender);
                    }
                }
            }
        }

        // Небольшая пауза, чтобы не нагружать процессор на 100% в цикле
        std::this_thread::sleep_for(10ms);
    }
}

// --------------------------------------------------------------------
// Поток 1: Движение и Битвы
// --------------------------------------------------------------------
void game_thread_func() {
    // Создаем генератор
    auto generator = run_fight_search();
    
    // Запускаем корутину первый раз (доходим до первого yield или цикла)
    generator.h.resume();

    while (run_game && !generator.h.done()) {
        // Получаем пару из корутины
        auto pair = generator.h.promise().current_pair;
        auto attacker = pair.first;
        auto defender = pair.second;

        // Важно: проверяем живы ли они всё ещё (вдруг defender умер в предыдущей итерации)
        if (attacker && defender && attacker->is_alive() && defender->is_alive()) {
            // Visitor Pattern: Defender принимает Attacker'а
            bool success = defender->accept(attacker);
            if (success) {
                defender->must_die();
            }
        }

        // Возобновляем корутину (она продолжит искать следующую пару или уйдет на новый круг движения)
        generator.h.resume();
    }
}

// --------------------------------------------------------------------
// Поток 2: Вывод карты
// --------------------------------------------------------------------
void print_map_thread() {
    while (run_game) {
        // Локальный буфер карты 100x100
        std::vector<std::string> map(100, std::string(100, ' '));

        // 1. Быстро читаем состояние (под мьютексом игры)
        {
            std::lock_guard<std::mutex> lck(game_mtx);
            for (const auto& npc : array_npcs) {
                if (npc->is_alive()) {
                    // Ограничиваем координаты, чтобы не выйти за границы массива
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

        // 2. Медленно выводим (под мьютексом печати)
        {
            std::lock_guard<std::mutex> lck(print_mutex);
            
            // Очистка экрана (ANSI Escape codes)
            std::cout << "\033[2J\033[1;1H"; 
            std::cout << "Map Snapshot:" << std::endl;
            
            // Рисуем верхнюю рамку
            for(int i=0; i<102; ++i) std::cout << "-";
            std::cout << std::endl;

            for (int i = 0; i < 100; ++i) {
                std::cout << "|"; // Левая рамка
                for (int j = 0; j < 100; ++j) {
                     std::cout << map[i][j];
                }
                std::cout << "|" << std::endl; // Правая рамка
            }
            
            for(int i=0; i<102; ++i) std::cout << "-";
            std::cout << std::endl;
        }

        // Ждем 1 секунду
        std::this_thread::sleep_for(1s);
    }
}

// --------------------------------------------------------------------
// Main
// --------------------------------------------------------------------
int main()
{
    std::srand(std::time(nullptr));

    std::cout << "Generating 50 NPCs..." << std::endl;
    // Генерируем монстров
    for (size_t i = 0; i < 50; ++i)
        array_npcs.insert(factory(NpcType(std::rand() % 3 + 1),
                             std::rand() % 100,
                             std::rand() % 100));

    // Запускаем потоки
    std::thread logic_thread(game_thread_func);
    std::thread render_thread(print_map_thread);

    // Играем 30 секунд
    std::this_thread::sleep_for(30s);
    run_game = false;

    // Ожидаем завершения потоков
    if (logic_thread.joinable()) logic_thread.join();
    if (render_thread.joinable()) render_thread.join();

    // Финальный вывод
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