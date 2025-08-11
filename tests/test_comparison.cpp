#include <gtest/gtest.h>
#include "../include/Vector.h"

// Equality Operator Tests
TEST(Comparison, EqualityOperator_TrueForEqualVectors) {
    Vector<int> vec1({1, 2, 3, 4, 5});
    Vector<int> vec2({1, 2, 3, 4, 5});
    
    EXPECT_TRUE(vec1 == vec2);
    EXPECT_TRUE(vec2 == vec1);
}

TEST(Comparison, EqualityOperator_FalseForDifferentElements) {
    Vector<int> vec1({1, 2, 3, 4, 5});
    Vector<int> vec2({1, 2, 3, 4, 6});
    
    EXPECT_FALSE(vec1 == vec2);
    EXPECT_FALSE(vec2 == vec1);
}

TEST(Comparison, EqualityOperator_FalseForDifferentSize) {
    Vector<int> vec1({1, 2, 3, 4, 5});
    Vector<int> vec2({1, 2, 3, 4});
    
    EXPECT_FALSE(vec1 == vec2);
    EXPECT_FALSE(vec2 == vec1);
}

TEST(Comparison, EqualityOperator_TrueForEmptyVectors) {
    Vector<int> vec1;
    Vector<int> vec2;
    
    EXPECT_TRUE(vec1 == vec2);
    EXPECT_TRUE(vec2 == vec1);
}

TEST(Comparison, EqualityOperator_FalseForEmptyVsNonEmpty) {
    Vector<int> vec1;
    Vector<int> vec2({1, 2, 3});
    
    EXPECT_FALSE(vec1 == vec2);
    EXPECT_FALSE(vec2 == vec1);
}

TEST(Comparison, EqualityOperator_WorksWithStrings) {
    Vector<std::string> vec1({"hello", "world", "test"});
    Vector<std::string> vec2({"hello", "world", "test"});
    Vector<std::string> vec3({"hello", "world", "different"});
    
    EXPECT_TRUE(vec1 == vec2);
    EXPECT_FALSE(vec1 == vec3);
}

TEST(Comparison, EqualityOperator_Reflexive) {
    Vector<int> vec({1, 2, 3, 4, 5});
    
    EXPECT_TRUE(vec == vec);
}

TEST(Comparison, EqualityOperator_Symmetric) {
    Vector<int> vec1({1, 2, 3, 4, 5});
    Vector<int> vec2({1, 2, 3, 4, 5});
    
    EXPECT_TRUE(vec1 == vec2);
    EXPECT_TRUE(vec2 == vec1);
}

// Inequality Operator Tests
TEST(Comparison, InequalityOperator_TrueWhenDifferent) {
    Vector<int> vec1({1, 2, 3, 4, 5});
    Vector<int> vec2({1, 2, 3, 4, 6});
    
    EXPECT_TRUE(vec1 != vec2);
    EXPECT_TRUE(vec2 != vec1);
}

TEST(Comparison, InequalityOperator_FalseWhenEqual) {
    Vector<int> vec1({1, 2, 3, 4, 5});
    Vector<int> vec2({1, 2, 3, 4, 5});
    
    EXPECT_FALSE(vec1 != vec2);
    EXPECT_FALSE(vec2 != vec1);
}

TEST(Comparison, InequalityOperator_TrueForDifferentSizes) {
    Vector<int> vec1({1, 2, 3, 4, 5});
    Vector<int> vec2({1, 2, 3, 4});
    
    EXPECT_TRUE(vec1 != vec2);
    EXPECT_TRUE(vec2 != vec1);
}

TEST(Comparison, InequalityOperator_FalseForEmptyVectors) {
    Vector<int> vec1;
    Vector<int> vec2;
    
    EXPECT_FALSE(vec1 != vec2);
    EXPECT_FALSE(vec2 != vec1);
}

TEST(Comparison, InequalityOperator_TrueForEmptyVsNonEmpty) {
    Vector<int> vec1;
    Vector<int> vec2({1, 2, 3});
    
    EXPECT_TRUE(vec1 != vec2);
    EXPECT_TRUE(vec2 != vec1);
}

TEST(Comparison, InequalityOperator_WorksWithStrings) {
    Vector<std::string> vec1({"hello", "world", "test"});
    Vector<std::string> vec2({"hello", "world", "test"});
    Vector<std::string> vec3({"hello", "world", "different"});
    
    EXPECT_FALSE(vec1 != vec2);
    EXPECT_TRUE(vec1 != vec3);
}

TEST(Comparison, InequalityOperator_Reflexive) {
    Vector<int> vec({1, 2, 3, 4, 5});
    
    EXPECT_FALSE(vec != vec);
}

TEST(Comparison, InequalityOperator_Symmetric) {
    Vector<int> vec1({1, 2, 3, 4, 5});
    Vector<int> vec2({1, 2, 3, 4, 6});
    
    EXPECT_TRUE(vec1 != vec2);
    EXPECT_TRUE(vec2 != vec1);
}

// Edge Cases
TEST(Comparison, Comparison_AfterModification) {
    Vector<int> vec1({1, 2, 3, 4, 5});
    Vector<int> vec2({1, 2, 3, 4, 5});
    
    EXPECT_TRUE(vec1 == vec2);
    
    vec1[0] = 999;
    EXPECT_FALSE(vec1 == vec2);
    EXPECT_TRUE(vec1 != vec2);
}

TEST(Comparison, Comparison_AfterPushBack) {
    Vector<int> vec1({1, 2, 3});
    Vector<int> vec2({1, 2, 3});
    
    EXPECT_TRUE(vec1 == vec2);
    
    vec1.push_back(4);
    EXPECT_FALSE(vec1 == vec2);
    EXPECT_TRUE(vec1 != vec2);
}

TEST(Comparison, Comparison_AfterPopBack) {
    Vector<int> vec1({1, 2, 3, 4, 5});
    Vector<int> vec2({1, 2, 3, 4, 5});
    
    EXPECT_TRUE(vec1 == vec2);
    
    vec1.pop_back();
    EXPECT_FALSE(vec1 == vec2);
    EXPECT_TRUE(vec1 != vec2);
}

TEST(Comparison, Comparison_AfterClear) {
    Vector<int> vec1({1, 2, 3, 4, 5});
    Vector<int> vec2({1, 2, 3, 4, 5});
    
    EXPECT_TRUE(vec1 == vec2);
    
    vec1.clear();
    EXPECT_FALSE(vec1 == vec2);
    EXPECT_TRUE(vec1 != vec2);
}

TEST(Comparison, Comparison_WithDifferentTypes) {
    Vector<std::string> vec1({"hello", "world"});
    Vector<std::string> vec2({"hello", "world"});
    Vector<std::string> vec3({"hello", "different"});
    
    EXPECT_TRUE(vec1 == vec2);
    EXPECT_FALSE(vec1 == vec3);
    EXPECT_TRUE(vec1 != vec3);
}

TEST(Comparison, Comparison_WithVectorsOfDifferentCapacities) {
    Vector<int> vec1(10);
    Vector<int> vec2(20);
    
    for (int i = 0; i < 5; ++i) {
        vec1.push_back(i);
        vec2.push_back(i);
    }
    
    EXPECT_TRUE(vec1 == vec2);
    EXPECT_FALSE(vec1 != vec2);
}

TEST(Comparison, Comparison_WithSelfAssignment) {
    Vector<int> vec({1, 2, 3, 4, 5});
    
    EXPECT_TRUE(vec == vec);
    EXPECT_FALSE(vec != vec);
}
