#include <gtest/gtest.h>
#include "five.h"
#include <stdexcept>

TEST(FiveTest, DefaultConstructor) {
    Five five;
    EXPECT_EQ(five.getSize(), 0);
    EXPECT_EQ(five.toString(), "0");
}

TEST(FiveTest, StringConstructor) {
    Five five("1234");
    EXPECT_EQ(five.toString(), "1234");
    
    Five five2("0");
    EXPECT_EQ(five2.toString(), "0");
}

TEST(FiveTest, StringConstructorInvalid) {
    EXPECT_THROW(Five("15"), std::invalid_argument); 
    EXPECT_THROW(Five("A"), std::invalid_argument);  
    EXPECT_THROW(Five(""), std::invalid_argument);
}

TEST(FiveTest, CopyConstructor) {
    Five original("1234");
    Five copy(original);
    EXPECT_EQ(copy.toString(), "1234");
    EXPECT_TRUE(original.equals(copy));
}

TEST(FiveTest, Equals) {
    Five five1("1234");
    Five five2("1234");
    Five five3("12");
    
    EXPECT_TRUE(five1.equals(five2));
    EXPECT_FALSE(five1.equals(five3));
}

TEST(FiveTest, Compare) {
    Five five1("12");
    Five five2("23");
    Five five3("12");
    
    EXPECT_TRUE(five1.isLess(five2));
    EXPECT_TRUE(five2.isGreater(five1));
    EXPECT_EQ(five1.compare(five3), 0);
}

TEST(FiveTest, Add) {
    Five five1("12");   
    Five five2("23");   
    Five result = five1.add(five2);
    EXPECT_EQ(result.toString(), "40"); 
    
    Five five3("4");  
    Five five4("1");  
    Five result2 = five3.add(five4);
    EXPECT_EQ(result2.toString(), "10"); 
}

TEST(FiveTest, AddWithZero) {
    Five five1("1234");
    Five five2("0");
    Five result = five1.add(five2);
    EXPECT_EQ(five1.toString(), "1234");
}

TEST(FiveTest, Subtract) {
    Five five1("40");   
    Five five2("23");   
    Five result = five1.subtract(five2);
    EXPECT_EQ(result.toString(), "12"); 
    
    Five five3("10"); 
    Five five4("1");   
    Five result2 = five3.subtract(five4);
    EXPECT_EQ(result2.toString(), "4"); 
}

TEST(FiveTest, SubtractEqual) {
    Five five1("1234");
    Five five2("1234");
    Five result = five1.subtract(five2);
    EXPECT_EQ(result.toString(), "0");
}

TEST(FiveTest, SubtractUnderflow) {
    Five five1("12");
    Five five2("1234");
    EXPECT_THROW(five1.subtract(five2), std::underflow_error);
}

TEST(FiveTest, LargeNumbers) {
    Five five1("4444");    
    Five five2("1");        
    Five result = five1.add(five2);
    EXPECT_EQ(result.toString(), "10000"); 
}

TEST(FiveTest, ToString) {
    Five five("1234");
    EXPECT_EQ(five.toString(), "1234");
}

TEST(FiveTest, Print) {
    Five five("1234");
    testing::internal::CaptureStdout();
    five.print();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "1234\n");
}

TEST(FiveTest, Immutability) {
    Five original("1234");
    Five other("23");
    
    Five sum = original.add(other);
    Five diff = original.subtract(other);
    
    EXPECT_EQ(original.toString(), "1234");
    EXPECT_EQ(other.toString(), "23");
}

TEST(FiveTest, EdgeCases) {
    Five five1("4");
    Five five2("1");
    Five result = five1.add(five2);
    EXPECT_EQ(result.toString(), "10");
    
    Five five3("1");
    Five five4("1");
    Five result2 = five3.subtract(five4);
    EXPECT_EQ(result2.toString(), "0");
}

TEST(FiveTest, ComplexOperations) {
    Five five1("123");
    Five five2("34");
    Five five3("2");
    
    Five temp = five1.add(five2);
    Five result = temp.subtract(five3);
    EXPECT_EQ(result.toString(), "210");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}