#include <gtest/gtest.h>
#include "../include/Vector.h"

TEST(VectorConstruction, DefaultConstructor) {
    Vector<int> vec;
    EXPECT_EQ(vec.size(), 0);
    EXPECT_EQ(vec.capacity(), 4);
}

TEST(VectorConstruction, CapacityConstructor) {
    Vector<int> vec(10);
    EXPECT_EQ(vec.size(), 0);
    EXPECT_EQ(vec.capacity(), 10);
}

TEST(VectorConstruction, InitializerListConstructor) {
    Vector<int> vec({1, 2, 3});
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
}
