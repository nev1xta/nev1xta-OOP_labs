#include <gtest/gtest.h>
#include <memory>
#include <sstream>
#include <npc.hpp>
#include <pegasus.hpp>
#include <dragon.hpp>
#include <knight.hpp>

TEST(NPCBasic, Creation) {
    Pegasus s("Nutty", 10, 20);
    EXPECT_EQ(s.getName(), "Nutty");
    EXPECT_EQ(s.getX(), 10);
    EXPECT_EQ(s.getY(), 20);
    EXPECT_TRUE(s.isAlive());
    EXPECT_EQ(s.getType(), PegasusType);
}


TEST(NPCDistance, DistanceCalculation) {
    auto a = std::make_shared<Dragon>("Merlin", 0, 0);
    auto b = std::make_shared<Pegasus>("Fluffy", 3, 4);
    double dist = a->distanceTo(b);
    EXPECT_NEAR(dist, 5.0, 0.0001);
}

TEST(NPCFight, KillRules) {
    auto knight = std::make_shared<Knight>("Thrall", 100, 100);
    auto dragon = std::make_shared<Dragon>("Malfurion", 105, 100);
    EXPECT_TRUE(dragon->isAlive());
    EXPECT_TRUE(knight->isAlive());
    auto dragon2  = std::make_shared<Dragon>("Cenarius", 50, 50);
    auto pegasus = std::make_shared<Pegasus>("Chip", 51, 50);
    dragon2->fight(pegasus);
    EXPECT_FALSE(pegasus->isAlive());
    EXPECT_TRUE(dragon2->isAlive());
    auto pegasus2 = std::make_shared<Pegasus>("Dale", 10, 10);
    auto knight2 = std::make_shared<Knight>("Garrosh", 15, 10);
    pegasus2->fight(knight2);
    EXPECT_TRUE(knight2->isAlive());
    EXPECT_TRUE(pegasus2->isAlive());
}

TEST(NPCFight, MutualKill) {
    auto knight = std::make_shared<Knight>("Grom", 100, 100);
    auto dragon = std::make_shared<Dragon>("Hamul", 100, 100);
    knight->fight(dragon);
    dragon->fight(knight);
    EXPECT_FALSE(dragon->isAlive());
    EXPECT_TRUE(knight->isAlive());
}

TEST(NPCSave, SaveToStream) {
    auto npc = std::make_shared<Pegasus>("Acorn", 30, 40);

    std::ostringstream oss;
    npc->save(oss);
    std::string expected = "1 Acorn 30 40\n";
    EXPECT_EQ(oss.str(), expected);
}

TEST(NPCDeath, DieOnce) {
    auto s = std::make_shared<Pegasus>("Victim", 0, 0);
    auto d = std::make_shared<Dragon>("Killer", 5, 0);
    d->fight(s);
    EXPECT_FALSE(s->isAlive());
    d->fight(s);
    EXPECT_FALSE(s->isAlive());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}