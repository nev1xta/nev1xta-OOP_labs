#include <gtest/gtest.h>
#include <memory>
#include "npc.h"
#include "pegasus.h"
#include "dragon.h"
#include "knight.h"

TEST(FightTest1, PegasusnAttacks) {
    auto pegasus = std::make_shared<Pegasus>(0, 0, "D1");
    auto victim = std::make_shared<Dragon>(0, 0, "K1");
    EXPECT_FALSE(victim->accept(pegasus));
}

TEST(FightTest2, KnightAttacks) {
    auto dragon = std::make_shared<Dragon>(0, 0, "K1");
    auto pegasus = std::make_shared<Pegasus>(0, 0, "D1");
    EXPECT_TRUE(pegasus->accept(dragon)); 
}

TEST(FightTest3, KnightAttacks) {
    auto knight = std::make_shared<Knight>(0, 0, "BK1");
    auto pegasus = std::make_shared<Pegasus>(0, 0, "D1");
    EXPECT_TRUE(pegasus->accept(knight));
}

TEST(LogicTest, DistanceCheck) {
    auto npc1 = std::make_shared<Pegasus>(0, 0, "D1");
    auto npc2 = std::make_shared<Dragon>(10, 0, "K1");
    
    EXPECT_TRUE(npc1->is_close(npc2, 10));
    EXPECT_FALSE(npc1->is_close(npc2, 9));
}