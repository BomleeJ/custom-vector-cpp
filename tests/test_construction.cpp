#include <gtest/gtest.h>
#include "Vector.h"
#include <string>

// Default Constructor Tests
TEST(Construction, DefaultConstructor_CreatesEmptyVectorLite) {
    VectorLite<int> vec;
    EXPECT_EQ(vec.size(), 0);
    EXPECT_EQ(vec.capacity(), 4);
    EXPECT_TRUE(vec.empty());
}

TEST(Construction, DefaultConstructor_WorksWithDifferentTypes) {
    VectorLite<double> vec1;
    VectorLite<std::string> vec2;
    
    EXPECT_EQ(vec1.size(), 0);
    EXPECT_EQ(vec2.size(), 0);
}

// Capacity Constructor Tests
TEST(Construction, CapacityConstructor_AllocatesCorrectCapacity) {
    VectorLite<int> vec(10);
    EXPECT_EQ(vec.size(), 0);
    EXPECT_EQ(vec.capacity(), 10);
    EXPECT_TRUE(vec.empty());
}

// Initializer List Constructor Tests
TEST(Construction, InitializerListConstructor_CopiesElementsCorrectly) {
    VectorLite<int> vec({1, 2, 3, 4, 5});
    EXPECT_EQ(vec.size(), 5);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
    EXPECT_EQ(vec[3], 4);
    EXPECT_EQ(vec[4], 5);
    EXPECT_FALSE(vec.empty());
}

TEST(Construction, InitializerListConstructor_WorksWithEmptyList) {
    VectorLite<int> vec({});
    EXPECT_EQ(vec.size(), 0);
    EXPECT_TRUE(vec.empty());
}

TEST(Construction, InitializerListConstructor_WorksWithStrings) {
    VectorLite<std::string> vec({"hello", "world", "test"});
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], "hello");
    EXPECT_EQ(vec[1], "world");
    EXPECT_EQ(vec[2], "test");
}

// Copy Constructor Tests
TEST(Construction, CopyConstructor_CreatesDeepCopy) {
    VectorLite<int> original({1, 2, 3, 4});
    VectorLite<int> copy(original);
    
    EXPECT_EQ(original.size(), copy.size());
    EXPECT_EQ(original.capacity(), copy.capacity());
    
    for (size_t i = 0; i < original.size(); ++i) {
        EXPECT_EQ(original[i], copy[i]);
    }
    
    original[0] = 999;
    EXPECT_NE(original[0], copy[0]);
    EXPECT_EQ(copy[0], 1);
}

TEST(Construction, CopyConstructor_WorksWithEmptyVectorLite) {
    VectorLite<int> original;
    VectorLite<int> copy(original);
    
    EXPECT_EQ(copy.size(), 0);
    EXPECT_EQ(copy.capacity(), 4);
    EXPECT_TRUE(copy.empty());
}

// Move Constructor Tests
TEST(Construction, MoveConstructor_TakesOwnershipAndInvalidatesSource) {
    VectorLite<int> original({1, 2, 3, 4, 5});
    VectorLite<int> moved(std::move(original));
    
    EXPECT_EQ(moved.size(), 5);
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(moved[i], i + 1);
    }
    
    EXPECT_EQ(original.size(), 0);
    EXPECT_EQ(original.capacity(), 4);
    EXPECT_TRUE(original.empty());
}

TEST(Construction, MoveConstructor_WorksWithEmptyVectorLite) {
    VectorLite<int> original;
    VectorLite<int> moved(std::move(original));
    
    EXPECT_EQ(moved.size(), 0);
    EXPECT_EQ(moved.capacity(), 4);
    EXPECT_TRUE(moved.empty());
    
    EXPECT_EQ(original.size(), 0);
    EXPECT_EQ(original.capacity(), 4);
    EXPECT_TRUE(original.empty());
}