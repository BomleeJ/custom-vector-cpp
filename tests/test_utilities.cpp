#include <gtest/gtest.h>
#include "../include/Vector.h"

// Size Tests
TEST(Utilities, Size_ReturnsCorrectElementCount) {
    Vector<int> vec;
    EXPECT_EQ(vec.size(), 0);
    
    vec.push_back(1);
    EXPECT_EQ(vec.size(), 1);
    
    vec.push_back(2);
    EXPECT_EQ(vec.size(), 2);
    
    vec.push_back(3);
    EXPECT_EQ(vec.size(), 3);
}

TEST(Utilities, Size_AfterPopBack) {
    Vector<int> vec({1, 2, 3, 4, 5});
    EXPECT_EQ(vec.size(), 5);
    
    vec.pop_back();
    EXPECT_EQ(vec.size(), 4);
    
    vec.pop_back();
    EXPECT_EQ(vec.size(), 3);
    
    vec.pop_back();
    EXPECT_EQ(vec.size(), 2);
    
    vec.pop_back();
    EXPECT_EQ(vec.size(), 1);
    
    vec.pop_back();
    EXPECT_EQ(vec.size(), 0);
}

TEST(Utilities, Size_AfterClear) {
    Vector<int> vec({1, 2, 3, 4, 5});
    EXPECT_EQ(vec.size(), 5);
    
    vec.clear();
    EXPECT_EQ(vec.size(), 0);
}

TEST(Utilities, Size_AfterCopyConstruction) {
    Vector<int> original({1, 2, 3, 4, 5});
    Vector<int> copy(original);
    
    EXPECT_EQ(original.size(), 5);
    EXPECT_EQ(copy.size(), 5);
}

TEST(Utilities, Size_AfterMoveConstruction) {
    Vector<int> original({1, 2, 3, 4, 5});
    Vector<int> moved(std::move(original));
    
    EXPECT_EQ(moved.size(), 5);
    EXPECT_EQ(original.size(), 0);
}

TEST(Utilities, Size_AfterCopyAssignment) {
    Vector<int> original({1, 2, 3, 4, 5});
    Vector<int> copy({10, 20, 30});
    
    copy = original;
    EXPECT_EQ(original.size(), 5);
    EXPECT_EQ(copy.size(), 5);
}

TEST(Utilities, Size_AfterMoveAssignment) {
    Vector<int> original({1, 2, 3, 4, 5});
    Vector<int> moved({10, 20, 30});
    
    moved = std::move(original);
    EXPECT_EQ(moved.size(), 5);
    EXPECT_EQ(original.size(), 0);
}

// Capacity Tests
TEST(Utilities, Capacity_DoublesOnResize) {
    Vector<int> vec(2);
    
    vec.push_back(1);
    EXPECT_EQ(vec.capacity(), 2);
    
    vec.push_back(2);
    EXPECT_EQ(vec.capacity(), 2);
    
    vec.push_back(3);
    EXPECT_GT(vec.capacity(), 2);
    EXPECT_EQ(vec.size(), 3);
}

TEST(Utilities, Capacity_InitialCapacityConstructor) {
    Vector<int> vec(10);
    EXPECT_EQ(vec.capacity(), 10);
    EXPECT_EQ(vec.size(), 0);
}

TEST(Utilities, Capacity_DefaultConstructor) {
    Vector<int> vec;
    EXPECT_EQ(vec.capacity(), 4);
    EXPECT_EQ(vec.size(), 0);
}

TEST(Utilities, Capacity_AfterClear) {
    Vector<int> vec({1, 2, 3, 4, 5});
    size_t original_capacity = vec.capacity();
    
    vec.clear();
    EXPECT_EQ(vec.capacity(), original_capacity);
    EXPECT_EQ(vec.size(), 0);
}

TEST(Utilities, Capacity_AfterCopyConstruction) {
    Vector<int> original({1, 2, 3, 4, 5});
    Vector<int> copy(original);
    
    EXPECT_EQ(original.capacity(), copy.capacity());
}

TEST(Utilities, Capacity_AfterMoveConstruction) {
    Vector<int> original({1, 2, 3, 4, 5});
    size_t original_capacity = original.capacity();
    
    Vector<int> moved(std::move(original));
    EXPECT_EQ(moved.capacity(), original_capacity);
    EXPECT_EQ(original.capacity(), 4);
}

TEST(Utilities, Capacity_AfterCopyAssignment) {
    Vector<int> original({1, 2, 3, 4, 5});
    Vector<int> copy({10, 20, 30});
    size_t original_capacity = original.capacity();
    
    copy = original;
    EXPECT_EQ(copy.capacity(), original_capacity);
}

TEST(Utilities, Capacity_AfterMoveAssignment) {
    Vector<int> original({1, 2, 3, 4, 5});
    Vector<int> moved({10, 20, 30});
    size_t original_capacity = original.capacity();
    
    moved = std::move(original);
    EXPECT_EQ(moved.capacity(), original_capacity);
    EXPECT_EQ(original.capacity(), 4);
}

// Empty Tests
TEST(Utilities, Empty_TrueForNewVector) {
    Vector<int> vec;
    EXPECT_TRUE(vec.empty());
}

TEST(Utilities, Empty_FalseAfterPushBack) {
    Vector<int> vec;
    EXPECT_TRUE(vec.empty());
    
    vec.push_back(1);
    EXPECT_FALSE(vec.empty());
}

TEST(Utilities, Empty_TrueAfterClear) {
    Vector<int> vec({1, 2, 3, 4, 5});
    EXPECT_FALSE(vec.empty());
    
    vec.clear();
    EXPECT_TRUE(vec.empty());
}

TEST(Utilities, Empty_TrueAfterPopBack) {
    Vector<int> vec({1, 2, 3});
    
    vec.pop_back();
    EXPECT_FALSE(vec.empty());
    
    vec.pop_back();
    EXPECT_FALSE(vec.empty());
    
    vec.pop_back();
    EXPECT_TRUE(vec.empty());
}

TEST(Utilities, Empty_AfterCopyConstruction) {
    Vector<int> original({1, 2, 3, 4, 5});
    Vector<int> copy(original);
    
    EXPECT_FALSE(original.empty());
    EXPECT_FALSE(copy.empty());
}

TEST(Utilities, Empty_AfterMoveConstruction) {
    Vector<int> original({1, 2, 3, 4, 5});
    Vector<int> moved(std::move(original));
    
    EXPECT_TRUE(original.empty());
    EXPECT_FALSE(moved.empty());
}

TEST(Utilities, Empty_AfterCopyAssignment) {
    Vector<int> original({1, 2, 3, 4, 5});
    Vector<int> copy;
    
    copy = original;
    EXPECT_FALSE(original.empty());
    EXPECT_FALSE(copy.empty());
}

TEST(Utilities, Empty_AfterMoveAssignment) {
    Vector<int> original({1, 2, 3, 4, 5});
    Vector<int> moved;
    
    moved = std::move(original);
    EXPECT_TRUE(original.empty());
    EXPECT_FALSE(moved.empty());
}

TEST(Utilities, Empty_WithEmptyInitializerList) {
    Vector<int> vec({});
    EXPECT_TRUE(vec.empty());
}

TEST(Utilities, Empty_WithNonEmptyInitializerList) {
    Vector<int> vec({1, 2, 3});
    EXPECT_FALSE(vec.empty());
}

// Combined Tests
TEST(Utilities, SizeCapacityEmpty_Consistency) {
    Vector<int> vec;
    
    EXPECT_EQ(vec.size(), 0);
    EXPECT_GT(vec.capacity(), 0);
    EXPECT_TRUE(vec.empty());
    
    vec.push_back(1);
    EXPECT_EQ(vec.size(), 1);
    EXPECT_GT(vec.capacity(), 0);
    EXPECT_FALSE(vec.empty());
    
    vec.push_back(2);
    vec.push_back(3);
    EXPECT_EQ(vec.size(), 3);
    EXPECT_GT(vec.capacity(), 0);
    EXPECT_FALSE(vec.empty());
    
    vec.clear();
    EXPECT_EQ(vec.size(), 0);
    EXPECT_GT(vec.capacity(), 0);
    EXPECT_TRUE(vec.empty());
}

TEST(Utilities, SizeCapacityEmpty_WithDifferentTypes) {
    Vector<std::string> vec;
    
    EXPECT_EQ(vec.size(), 0);
    EXPECT_GT(vec.capacity(), 0);
    EXPECT_TRUE(vec.empty());
    
    vec.push_back("hello");
    EXPECT_EQ(vec.size(), 1);
    EXPECT_GT(vec.capacity(), 0);
    EXPECT_FALSE(vec.empty());
    
    vec.clear();
    EXPECT_EQ(vec.size(), 0);
    EXPECT_GT(vec.capacity(), 0);
    EXPECT_TRUE(vec.empty());
}

TEST(Utilities, SizeCapacityEmpty_AfterReuse) {
    Vector<int> vec;
    
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    EXPECT_EQ(vec.size(), 3);
    EXPECT_FALSE(vec.empty());
    
    vec.clear();
    EXPECT_EQ(vec.size(), 0);
    EXPECT_TRUE(vec.empty());
    
    vec.push_back(10);
    vec.push_back(20);
    EXPECT_EQ(vec.size(), 2);
    EXPECT_FALSE(vec.empty());
}
