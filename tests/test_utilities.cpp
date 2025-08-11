#include <gtest/gtest.h>
#include "Vector.h"
#include <stdexcept>

TEST(Utilities, Reserve)
{
    VectorLite<int> myVec;
    size_t spaces = 100;
    myVec.reserve(spaces);
    EXPECT_EQ(myVec.capacity(), spaces);
}

TEST(Utilities, Comparisons)
{
    
    VectorLite<int> VecA({1, 2, 3, 4, 5});
    VectorLite<int> VecB({1, 2, 3, 4, 5});

    EXPECT_TRUE(VecA == VecB);
    EXPECT_FALSE(VecA != VecB);
    VecB.push_back(6);
    EXPECT_FALSE(VecA == VecB);
    EXPECT_TRUE(VecA != VecB);
}

TEST(Utilities, Clear)
{
    VectorLite<int> myVec;
    myVec.push_back(10);
    EXPECT_TRUE(myVec.size() == 1);
    myVec.clear();
    EXPECT_TRUE(myVec.size() == 0);

}

TEST(Utilities, EmptyWhenInitialized)
{
    VectorLite<int> myVec;
    EXPECT_TRUE(myVec.empty() == 1);
}

TEST(Utilities, EmptyAfterClear)
{
    VectorLite<int> myVec({1, 2, 3, 4, 5});
    myVec.clear();
    EXPECT_TRUE(myVec.empty() == 1);
}