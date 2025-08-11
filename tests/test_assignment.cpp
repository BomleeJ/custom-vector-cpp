#include <gtest/gtest.h>
#include "Vector.h"

// Copy Assignment Tests
TEST(Assignment, CopyAssignment_DeepCopiesContents) {
    VectorLite<int> original({1, 2, 3, 4, 5});
    VectorLite<int> copy({10, 20, 30});
    
    copy = original;
    
    EXPECT_EQ(original.size(), copy.size());
    EXPECT_EQ(original.capacity(), copy.capacity());
    
    for (size_t i = 0; i < original.size(); ++i) {
        EXPECT_EQ(original[i], copy[i]);
    }
    
    original[0] = 999;
    EXPECT_NE(original[0], copy[0]);
    EXPECT_EQ(copy[0], 1);
}

TEST(Assignment, CopyAssignment_WorksWithEmptyVectorLite) {
    VectorLite<int> original;
    VectorLite<int> copy({1, 2, 3});
    
    copy = original;
    
    EXPECT_EQ(copy.size(), 0);
    EXPECT_EQ(copy.capacity(), 4);
    EXPECT_TRUE(copy.empty());
}

TEST(Assignment, CopyAssignment_OverwritesExistingData) {
    VectorLite<int> original({1, 2, 3});
    VectorLite<int> copy({10, 20, 30, 40, 50});
    
    copy = original;
    
    EXPECT_EQ(copy.size(), 3);
    EXPECT_EQ(copy[0], 1);
    EXPECT_EQ(copy[1], 2);
    EXPECT_EQ(copy[2], 3);
}

// Move Assignment Tests
TEST(Assignment, MoveAssignment_TransfersOwnership) {
    VectorLite<int> original({1, 2, 3, 4, 5});
    VectorLite<int> moved({10, 20, 30});
    
    moved = std::move(original);
    
    EXPECT_EQ(moved.size(), 5);
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(moved[i], i + 1);
    }
    
}

TEST(Assignment, MoveAssignment_WorksWithEmptyVectorLite) {
    VectorLite<int> original;
    VectorLite<int> moved({1, 2, 3});
    
    moved = std::move(original);
    
    EXPECT_EQ(moved.size(), 0);
    EXPECT_EQ(moved.capacity(), 4);
    EXPECT_TRUE(moved.empty());
    

}

// Self Assignment Tests
TEST(Assignment, CopyAssignment_SelfAssignmentSafe) {
    VectorLite<int> vec({1, 2, 3, 4, 5});
    size_t original_size = vec.size();
    size_t original_capacity = vec.capacity();
    
    vec = vec;
    
    EXPECT_EQ(vec.size(), original_size);
    EXPECT_EQ(vec.capacity(), original_capacity);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
    EXPECT_EQ(vec[3], 4);
    EXPECT_EQ(vec[4], 5);
}

TEST(Assignment, MoveAssignment_SelfAssignmentSafe) {
    VectorLite<int> vec({1, 2, 3, 4, 5});
    size_t original_size = vec.size();
    size_t original_capacity = vec.capacity();
    
    vec = std::move(vec);
    
    EXPECT_EQ(vec.size(), original_size);
    EXPECT_EQ(vec.capacity(), original_capacity);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
    EXPECT_EQ(vec[3], 4);
    EXPECT_EQ(vec[4], 5);
}

// Chained Assignment Tests
TEST(Assignment, ChainedCopyAssignment) {
    VectorLite<int> a({1, 2, 3});
    VectorLite<int> b({4, 5, 6});
    VectorLite<int> c({7, 8, 9});
    
    a = b = c;
    
    EXPECT_EQ(a.size(), 3);
    EXPECT_EQ(b.size(), 3);
    EXPECT_EQ(c.size(), 3);
    
    for (int i = 0; i < 3; ++i) {
        EXPECT_EQ(a[i], 7 + i);
        EXPECT_EQ(b[i], 7 + i);
        EXPECT_EQ(c[i], 7 + i);
    }
}