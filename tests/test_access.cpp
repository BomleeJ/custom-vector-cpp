#include <gtest/gtest.h>
#include "Vector.h"
#include <stdexcept>

TEST(Access, BracketOperator_ReadWriteAccessCorrect) {
    VectorLite<int> vec({1, 2, 3, 4, 5});
    
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
    const VectorLite<int> vec({1, 2, 3, 4, 5});
    
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
    EXPECT_EQ(vec[3], 4);
    EXPECT_EQ(vec[4], 5);

}

TEST(Access, AtOperator_ReturnsCorrectElement) {
    VectorLite<int> vec({1, 2, 3, 4, 5});
    
    EXPECT_EQ(vec.at(0), 1);
    EXPECT_EQ(vec.at(1), 2);
    EXPECT_EQ(vec.at(2), 3);
    EXPECT_EQ(vec.at(3), 4);
    EXPECT_EQ(vec.at(4), 5);
}


TEST(Access, AtOperator_ThrowsOnOutOfBounds) {
    VectorLite<int> vec({1, 2, 3, 4, 5});
    
    EXPECT_THROW(vec.at(5), std::out_of_range);
    EXPECT_THROW(vec.at(10), std::out_of_range);
}

TEST(Access, BracketVsAt_ConsistentBehavior) {
    VectorLite<int> vec({1, 2, 3, 4, 5});
    
    for (size_t i = 0; i < vec.size(); ++i) {
        EXPECT_EQ(vec[i], vec.at(i));
    }
}