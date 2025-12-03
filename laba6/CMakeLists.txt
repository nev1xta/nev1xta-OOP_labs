cmake_minimum_required(VERSION 3.14)
project(NpcBattle LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Загрузка googletest через FetchContent
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.0
)
FetchContent_MakeAvailable(googletest)

# Основное исполняемое приложение
add_executable(npc_battle
    main.cpp
    src/npc.cpp
    src/pegasus.cpp
    src/dragon.cpp
    src/knight.cpp
)
target_include_directories(npc_battle PRIVATE include)

# Исполняемый файл для тестов
add_executable(npc_tests
    test/main_test.cpp
    src/npc.cpp
    src/pegasus.cpp
    src/dragon.cpp
    src/knight.cpp
)
target_include_directories(npc_tests PRIVATE include)

# Подключение gtest с использованием импортированных целей
target_link_libraries(npc_tests PRIVATE 
    GTest::gtest_main 
    GTest::gtest 
    GTest::gmock
)