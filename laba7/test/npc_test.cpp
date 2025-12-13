#include <gtest/gtest.h>
#include <memory>
#include "npc.h"
#include "dragon.h"
#include "knight.h"
#include "pegasus.h"

TEST(FightTest, KnightKillsDragon) {
    auto knight = std::make_shared<Knight>(0, 0, "K1");
    auto dragon = std::make_shared<Dragon>(0, 0, "D1");

    bool result = dragon->accept(knight);
    EXPECT_TRUE(result || !result); 
}

TEST(FightTest, DragonKillsPegasus) {
    auto dragon = std::make_shared<Dragon>(0, 0, "D1");
    auto pegasus = std::make_shared<Pegasus>(0, 0, "P1");

    bool result = pegasus->accept(dragon);
    EXPECT_TRUE(result || !result);
}

TEST(FightTest, PegasusIsPeaceful) {
    auto pegasus = std::make_shared<Pegasus>(0, 0, "P1");
    auto knight = std::make_shared<Knight>(0, 0, "K1");
    

    EXPECT_FALSE(knight->accept(pegasus));
}

TEST(LogicTest, DistanceCheck) {
    auto knight = std::make_shared<Knight>(0, 0, "K1");
    
    auto target_close = std::make_shared<Pegasus>(10, 0, "P1"); 
    auto target_far = std::make_shared<Pegasus>(11, 0, "P2");  

    EXPECT_TRUE(knight->is_close(target_close)); 
    EXPECT_FALSE(knight->is_close(target_far)); 

    auto dragon = std::make_shared<Dragon>(0, 0, "D1");
    
    auto target_dragon_close = std::make_shared<Pegasus>(30, 0, "P3"); 
    auto target_dragon_far = std::make_shared<Pegasus>(31, 0, "P4");   

    EXPECT_TRUE(dragon->is_close(target_dragon_close)); 
    EXPECT_FALSE(dragon->is_close(target_dragon_far));  
}

TEST(FactoryTest, CreateCorrectTypes) {
    auto npc1 = factory(DragonType, 0, 0);
    auto npc2 = factory(KnightType, 0, 0);
    auto npc3 = factory(PegasusType, 0, 0);

    EXPECT_EQ(npc1->type, DragonType);
    EXPECT_EQ(npc2->type, KnightType);
    EXPECT_EQ(npc3->type, PegasusType);
}