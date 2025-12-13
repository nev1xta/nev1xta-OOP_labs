#include<gtest/gtest.h>

#include<queue.hpp>

TEST(Queue, Empty) {
    Queue<int> q;
    EXPECT_TRUE(q.empty());
}

TEST(Queue, NotEmpty) {
    Queue<int> q;
    q.push(1);
    EXPECT_FALSE(q.empty());
}

TEST(Queue, init_list) {
    Queue<int> q({1, 2, 3});
    EXPECT_FALSE(q.empty());
}

TEST(Queue, Push) {
    Queue<int> q;
    q.push(1);
    EXPECT_FALSE(q.empty());
}

TEST(Queue, Pop) {
    Queue<int> q;
    q.push(1);
    q.pop();
    EXPECT_TRUE(q.empty());
}

TEST(Queue, Front) {
    Queue<int> q;
    q.push(1);
    EXPECT_EQ(q.front(), 1);
}

TEST(Queue, Size) {
    Queue<int> q;
    q.push(1);
    EXPECT_EQ(q.size(), 1);
}

TEST(Queue, Operator) {
    Queue<int> q;
    q.push(1);
    EXPECT_EQ(q[0], 1);
}

TEST(Queue, CopyConstructor) {
    Queue<int> q;
    q.push(1);
    Queue<int> q2(q);
    EXPECT_EQ(q2.front(), 1);
}

TEST(Queue, MoveConstructor) {
    Queue<int> q;
    q.push(1);
    Queue<int> q2(std::move(q));
    EXPECT_EQ(q2.front(), 1);
}

TEST(Queue, CopyAssignment) {
    Queue<int> q;
    q.push(1);
    Queue<int> q2 = q;
    EXPECT_EQ(q2.front(), 1);
}

TEST(Queue, MoveAssignment) {
    Queue<int> q;
    q.push(1);
    Queue<int> q2;
    q2 = std::move(q);
    EXPECT_EQ(q2.front(), 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}