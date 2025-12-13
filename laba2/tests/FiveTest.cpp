#include <gtest/gtest.h>
#include "Five.h"

TEST(FiveTest, Basic) {
    Five num1;
    Five num2("123");
    Five num3(num2);
    
    EXPECT_TRUE(num2.eq(num3));
}

TEST(FiveTest, Add) {
    Five a("10");  
    Five b("20");  
    Five c = a.sum(b);
    
    Five expected("300"); 
    EXPECT_TRUE(c.eq(expected));
}

TEST(FiveTest, Compare) {
    Five a("10");
    Five b("20");
    
    EXPECT_TRUE(a.lt(b));
    EXPECT_TRUE(b.mt(a));
}

TEST(FiveTest, Sub) {
    Five a("30");
    Five b("20");
    Five c = a.sub(b);
    
    Five expected("100");
    EXPECT_TRUE(c.eq(expected));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}