#include <gtest/gtest.h>
#include "../include/Vector.h"
#include <stdexcept>

// Push Back Tests
TEST(Modifiers, PushBack_Lvalue_AddsElement) {
    Vector<int> vec;
    int value = 42;
    
    vec.push_back(value);
    
    EXPECT_EQ(vec.size(), 1);
    EXPECT_EQ(vec[0], 42);
    EXPECT_FALSE(vec.empty());
}

TEST(Modifiers, PushBack_MultipleElements) {
    Vector<int> vec;
    
    for (int i = 0; i < 10; ++i) {
        vec.push_back(i);
    }
    
    EXPECT_EQ(vec.size(), 10);
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(vec[i], i);
    }
}

TEST(Modifiers, PushBack_Rvalue_AddsElementViaMove) {
    Vector<std::string> vec;
    std::string value = "hello";
    
    vec.push_back(std::move(value));
    
    EXPECT_EQ(vec.size(), 1);
    EXPECT_EQ(vec[0], "hello");
    EXPECT_TRUE(value.empty());
}

TEST(Modifiers, PushBack_TriggersResize) {
    Vector<int> vec(2);
    
    vec.push_back(1);
    vec.push_back(2);
    EXPECT_EQ(vec.capacity(), 2);
    
    vec.push_back(3);
    EXPECT_GT(vec.capacity(), 2);
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
}

// Pop Back Tests
TEST(Modifiers, PopBack_RemovesLastElement) {
    Vector<int> vec({1, 2, 3, 4, 5});
    size_t original_size = vec.size();
    
    vec.pop_back();
    
    EXPECT_EQ(vec.size(), original_size - 1);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
    EXPECT_EQ(vec[3], 4);
}

TEST(Modifiers, PopBack_MultipleElements) {
    Vector<int> vec({1, 2, 3, 4, 5});
    
    vec.pop_back();
    vec.pop_back();
    vec.pop_back();
    
    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
}

TEST(Modifiers, PopBack_OnEmpty_UndefinedButSafe) {
    Vector<int> vec;
    
    vec.pop_back();
    
    EXPECT_EQ(vec.size(), 0);
    EXPECT_TRUE(vec.empty());
}

// Pop Tests (Exception-based pop_back)
TEST(Modifiers, Pop_ThrowsOnEmptyVector) {
    Vector<int> vec;
    
    EXPECT_THROW(vec.pop(), std::out_of_range);
}

TEST(Modifiers, Pop_WorksOnNonEmptyVector) {
    Vector<int> vec({1, 2, 3, 4, 5});
    size_t original_size = vec.size();
    
    vec.pop();
    
    EXPECT_EQ(vec.size(), original_size - 1);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
    EXPECT_EQ(vec[3], 4);
}

TEST(Modifiers, Pop_MultipleElements) {
    Vector<int> vec({1, 2, 3, 4, 5});
    
    vec.pop();
    vec.pop();
    vec.pop();
    
    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    
    vec.pop();
    vec.pop();
    
    EXPECT_EQ(vec.size(), 0);
    EXPECT_TRUE(vec.empty());
    
    EXPECT_THROW(vec.pop(), std::out_of_range);
}

// Clear Tests
TEST(Modifiers, Clear_EmptiesVectorAndPreservesCapacity) {
    Vector<int> vec({1, 2, 3, 4, 5});
    size_t original_capacity = vec.capacity();
    
    vec.clear();
    
    EXPECT_EQ(vec.size(), 0);
    EXPECT_EQ(vec.capacity(), original_capacity);
    EXPECT_TRUE(vec.empty());
}

TEST(Modifiers, Clear_OnEmptyVector) {
    Vector<int> vec;
    size_t original_capacity = vec.capacity();
    
    vec.clear();
    
    EXPECT_EQ(vec.size(), 0);
    EXPECT_EQ(vec.capacity(), original_capacity);
    EXPECT_TRUE(vec.empty());
}

TEST(Modifiers, Clear_AllowsReuse) {
    Vector<int> vec({1, 2, 3, 4, 5});
    
    vec.clear();
    EXPECT_EQ(vec.size(), 0);
    
    vec.push_back(10);
    vec.push_back(20);
    
    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec[0], 10);
    EXPECT_EQ(vec[1], 20);
}

// Mixed Operations Tests
TEST(Modifiers, PushAndPop_InterleavedOperationsStayConsistent) {
    Vector<int> vec;
    
    vec.push_back(1);
    vec.push_back(2);
    vec.pop_back();
    vec.push_back(3);
    vec.push_back(4);
    vec.pop_back();
    vec.push_back(5);
    
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 3);
    EXPECT_EQ(vec[2], 5);
}

TEST(Modifiers, Resize_MaintainsExistingElementsCorrectly) {
    Vector<int> vec(2);
    
    vec.push_back(1);
    vec.push_back(2);
    EXPECT_EQ(vec.capacity(), 2);
    
    vec.push_back(3);
    EXPECT_GT(vec.capacity(), 2);
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
    
    vec.push_back(4);
    vec.push_back(5);
    EXPECT_EQ(vec.size(), 5);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
    EXPECT_EQ(vec[3], 4);
    EXPECT_EQ(vec[4], 5);
}
