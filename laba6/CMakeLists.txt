cmake_minimum_required(VERSION 3.10)
project(BattleSimulation VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0
)
FetchContent_MakeAvailable(googletest)

find_package(Threads REQUIRED) # <--- Добавили поиск потоков

set(LIB_SOURCES
    src/npc.cpp
    src/dragon.cpp
    src/knight.cpp
    src/pegasus.cpp
    src/fight_io.cpp
)

set(HEADERS
    include/npc.h
    include/dragon.h
    include/knight.h
    include/pegasus.h
    include/fight_io.h
)

add_executable(battle_sim src/main.cpp ${LIB_SOURCES})
target_include_directories(battle_sim PRIVATE include)
target_compile_features(battle_sim PRIVATE cxx_std_20)
target_link_libraries(battle_sim Threads::Threads) # <--- Линкуем потоки

add_executable(npc_tests test/npc_test.cpp ${LIB_SOURCES})
target_include_directories(npc_tests PRIVATE include)
target_compile_features(npc_tests PRIVATE cxx_std_20)
target_link_libraries(npc_tests GTest::gtest GTest::gtest_main Threads::Threads)