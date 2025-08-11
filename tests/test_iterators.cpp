#include <gtest/gtest.h>
#include "Vector.h"
#include <algorithm>

TEST(Iterators, BasicIteration)
{
    VectorLite<int> myVec({0, 1, 2, 3, 4});
    
    int expected = 0;
    for (auto it = myVec.begin(); it != myVec.end(); ++it) {
        EXPECT_EQ(*it, expected);
        expected++;
    }
    
    expected = 0;
    for (const auto& value : myVec) {
        EXPECT_EQ(value, expected);
        expected++;
    }
}

TEST(Iterators, IncrementDecrement)
{
    VectorLite<int> myVec({10, 20, 30, 40, 50});
    auto it = myVec.begin();
    
    EXPECT_EQ(*it, 10);
    EXPECT_EQ(*(++it), 20);
    EXPECT_EQ(*(it++), 20);
    EXPECT_EQ(*it, 30);
    EXPECT_EQ(*(--it), 20);
    EXPECT_EQ(*(it--), 20);
    EXPECT_EQ(*it, 10);
}

TEST(Iterators, Comparisons)
{
    VectorLite<int> myVec({1, 2, 3, 4, 5});
    auto it1 = myVec.begin();
    auto it2 = myVec.begin();
    auto it3 = myVec.begin();
    ++it3;
    ++it3;
    
    EXPECT_TRUE(it1 == it2);
    EXPECT_FALSE(it1 == it3);
    EXPECT_TRUE(it1 != it3);
    EXPECT_FALSE(it1 != it2);
}

TEST(Iterators, STLAlgorithms)
{
    VectorLite<int> myVec({5, 2, 8, 1, 9, 3});
    
    auto found = std::find(myVec.begin(), myVec.end(), 8);
    EXPECT_NE(found, myVec.end());
    EXPECT_EQ(*found, 8);
    
    auto not_found = std::find(myVec.begin(), myVec.end(), 99);
    EXPECT_EQ(not_found, myVec.end());
    
    int count = std::count(myVec.begin(), myVec.end(), 2);
    EXPECT_EQ(count, 1);
    
    std::replace(myVec.begin(), myVec.end(), 8, 99);
    auto replaced = std::find(myVec.begin(), myVec.end(), 99);
    EXPECT_NE(replaced, myVec.end());
    EXPECT_EQ(*replaced, 99);
}

TEST(Iterators, EdgeCases)
{
    VectorLite<int> empty;
    EXPECT_EQ(empty.begin(), empty.end());
    
    VectorLite<int> single({42});
    EXPECT_NE(single.begin(), single.end());
    EXPECT_EQ(*single.begin(), 42);
    
    const VectorLite<int> const_vec({1, 2, 3});
    int expected = 1;
    for (auto it = const_vec.begin(); it != const_vec.end(); ++it) {
        EXPECT_EQ(*it, expected);
        expected++;
    }
    
    VectorLite<int> myVec({1, 2, 3});
    expected = 1;
    for (auto it = myVec.cbegin(); it != myVec.cend(); ++it) {
        EXPECT_EQ(*it, expected);
        expected++;
    }
}