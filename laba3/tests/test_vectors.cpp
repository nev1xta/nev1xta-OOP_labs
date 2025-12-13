#include <gtest/gtest.h>
#include <vector_points.h>
#include <vector_figure.h>
#include <point.h>
#include <hexagon.h>
#include<pentagon.h>

TEST(VectorPointsTest, AddAndGetPoints) {
    VectorPoints vp;
    Point p1(1, 2);
    Point p2(3, 4);
    vp.push(p1);
    vp.push(p2);
    EXPECT_EQ(vp.len(), 2);
    EXPECT_TRUE(vp.get(0) == p1);
    EXPECT_TRUE(vp.get(1) == p2);
}

TEST(VectorFigureTest, AddAndTotalArea) {
    VectorFigure vf;
    Pentagon pentagon;
    Hexagon hexagon(Point(0,0), Point(3,0), Point(0,4), Point(1,4), Point(3,4), Point(6,4));
    vf.push(&pentagon);
    vf.push(&hexagon);
    EXPECT_EQ(vf.len(), 2);
}