#include <gtest/gtest.h>
#include <point.h>
#include <hexagon.h>
#include <pentagon.h>
#include <octagon.h>

TEST(HexagleTest, AreaCalculation) {
    Point p1(0, 0);
    Point p2(3, 0);
    Point p3(0, 4);
    Point p4(1, 4);
    Point p5(3, 4);
    Point p6(6, 4);
    Hexagon hexagon(p1, p2, p3, p4, p5, p6);
    EXPECT_NEAR(static_cast<double>(hexagon.Area()), 6.0, 1e-10);
}

TEST(PentagonTest, AreaCalculation) {
    Point p1(1, 1);
    Point p2(1, 2);
    Point p3(2, 2);
    Point p4(2, 1);
    Point p5(2, 3);
    Pentagon pentagon(p1, p2, p3, p4, p5);
    EXPECT_NEAR(static_cast<double>(pentagon.Area()), 1.0, 1e-10);
}