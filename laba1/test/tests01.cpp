#include <gtest/gtest.h>
#include "../include/def.h"


TEST(defTest, PositiveNumbers) {
    EXPECT_EQ(SearchN(2, 7), 6); 
    EXPECT_EQ(SearchN(10, 50), 50); 
}

TEST(gcdTest, NegativeNumbers) {
    EXPECT_EQ(SearchN(1, -3), 0); 
    EXPECT_EQ(SearchN(-1, 5), 5); 
}

TEST(gcdTest, EdgeCases) {
    EXPECT_EQ(SearchN(0, 0), 0);
    EXPECT_EQ(SearchN(0, 1), 0); 
    EXPECT_EQ(SearchN(100, 1), 0);
    EXPECT_EQ(SearchN(1, 100), 100); 
}

TEST(gcdTest, LargeNumbers) {
    EXPECT_EQ(SearchN(153, 1000000000), 999999891); 
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}