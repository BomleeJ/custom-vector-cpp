#include <gtest/gtest.h>
#include "../include/Vector.h"
#include <stdexcept>

// Bracket Operator Tests
TEST(Access, BracketOperator_ReadWriteAccessCorrect) {
    Vector<int> vec({1, 2, 3, 4, 5});
    
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
    EXPECT_EQ(vec[3], 4);
    EXPECT_EQ(vec[4], 5);
    
    vec[0] = 10;
    vec[1] = 20;
    vec[2] = 30;
    
    EXPECT_EQ(vec[0], 10);
    EXPECT_EQ(vec[1], 20);
    EXPECT_EQ(vec[2], 30);
    EXPECT_EQ(vec[3], 4);
    EXPECT_EQ(vec[4], 5);
}

TEST(Access, BracketOperator_ConstCorrectness) {
    const Vector<int> vec({1, 2, 3, 4, 5});
    
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
    EXPECT_EQ(vec[3], 4);
    EXPECT_EQ(vec[4], 5);
}

TEST(Access, BracketOperator_WorksWithStrings) {
    Vector<std::string> vec({"hello", "world", "test"});
    
    EXPECT_EQ(vec[0], "hello");
    EXPECT_EQ(vec[1], "world");
    EXPECT_EQ(vec[2], "test");
    
    vec[0] = "modified";
    vec[1] = "changed";
    
    EXPECT_EQ(vec[0], "modified");
    EXPECT_EQ(vec[1], "changed");
    EXPECT_EQ(vec[2], "test");
}

// At Operator Tests
TEST(Access, AtOperator_ReturnsCorrectElement) {
    Vector<int> vec({1, 2, 3, 4, 5});
    
    EXPECT_EQ(vec.at(0), 1);
    EXPECT_EQ(vec.at(1), 2);
    EXPECT_EQ(vec.at(2), 3);
    EXPECT_EQ(vec.at(3), 4);
    EXPECT_EQ(vec.at(4), 5);
}

TEST(Access, AtOperator_AllowsModification) {
    Vector<int> vec({1, 2, 3, 4, 5});
    
    vec.at(0) = 10;
    vec.at(1) = 20;
    vec.at(2) = 30;
    
    EXPECT_EQ(vec.at(0), 10);
    EXPECT_EQ(vec.at(1), 20);
    EXPECT_EQ(vec.at(2), 30);
    EXPECT_EQ(vec.at(3), 4);
    EXPECT_EQ(vec.at(4), 5);
}

TEST(Access, AtOperator_ThrowsOnOutOfBounds) {
    Vector<int> vec({1, 2, 3, 4, 5});
    
    EXPECT_THROW(vec.at(5), std::out_of_range);
    EXPECT_THROW(vec.at(10), std::out_of_range);
}

TEST(Access, AtOperator_ThrowsOnEmptyVector) {
    Vector<int> vec;
    
    EXPECT_THROW(vec.at(0), std::out_of_range);
    EXPECT_THROW(vec.at(1), std::out_of_range);
}

TEST(Access, AtOperator_ConstCorrectness) {
    const Vector<int> vec({1, 2, 3, 4, 5});
    
    EXPECT_EQ(vec.at(0), 1);
    EXPECT_EQ(vec.at(1), 2);
    EXPECT_EQ(vec.at(2), 3);
    EXPECT_EQ(vec.at(3), 4);
    EXPECT_EQ(vec.at(4), 5);
    
    EXPECT_THROW(vec.at(5), std::out_of_range);
}

// Comparison between operator[] and at()
TEST(Access, BracketVsAt_ConsistentBehavior) {
    Vector<int> vec({1, 2, 3, 4, 5});
    
    for (size_t i = 0; i < vec.size(); ++i) {
        EXPECT_EQ(vec[i], vec.at(i));
    }
}

TEST(Access, BracketVsAt_ModificationConsistency) {
    Vector<int> vec({1, 2, 3, 4, 5});
    
    vec[0] = 10;
    vec.at(1) = 20;
    
    EXPECT_EQ(vec[0], 10);
    EXPECT_EQ(vec.at(0), 10);
    EXPECT_EQ(vec[1], 20);
    EXPECT_EQ(vec.at(1), 20);
}

// Edge Cases
TEST(Access, Access_InvalidIndex_ThrowsException) {
    Vector<int> vec({1, 2, 3});
    
    EXPECT_THROW(vec.at(3), std::out_of_range);
    EXPECT_THROW(vec.at(100), std::out_of_range);
}

TEST(Access, Access_AfterModification) {
    Vector<int> vec({1, 2, 3, 4, 5});
    
    vec[2] = 999;
    EXPECT_EQ(vec.at(2), 999);
    
    vec.at(3) = 888;
    EXPECT_EQ(vec[3], 888);
}

TEST(Access, Access_WithDifferentTypes) {
    Vector<std::string> vec({"hello", "world", "test"});
    
    EXPECT_EQ(vec[0], "hello");
    EXPECT_EQ(vec.at(1), "world");
    
    vec[0] = "modified";
    vec.at(1) = "changed";
    
    EXPECT_EQ(vec[0], "modified");
    EXPECT_EQ(vec.at(1), "changed");
}

TEST(Access, Access_AfterPushBack) {
    Vector<int> vec({1, 2, 3});
    
    vec.push_back(4);
    EXPECT_EQ(vec[3], 4);
    EXPECT_EQ(vec.at(3), 4);
    
    vec.push_back(5);
    EXPECT_EQ(vec[4], 5);
    EXPECT_EQ(vec.at(4), 5);
}

TEST(Access, Access_AfterPopBack) {
    Vector<int> vec({1, 2, 3, 4, 5});
    
    vec.pop_back();
    EXPECT_EQ(vec.size(), 4);
    EXPECT_EQ(vec[3], 4);
    EXPECT_EQ(vec.at(3), 4);
    
    EXPECT_THROW(vec.at(4), std::out_of_range);
}

TEST(Access, Access_AfterClear) {
    Vector<int> vec({1, 2, 3, 4, 5});
    
    vec.clear();
    EXPECT_THROW(vec.at(0), std::out_of_range);
}
