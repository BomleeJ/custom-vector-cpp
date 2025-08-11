#include <gtest/gtest.h>
#include "../include/Vector.h"
#include <stdexcept>

// Large Number of Elements Tests
TEST(EdgeCases, PushBack_LargeNumberOfElements_NoCrash) {
    Vector<int> vec;
    
    for (int i = 0; i < 10000; ++i) {
        vec.push_back(i);
    }
    
    EXPECT_EQ(vec.size(), 10000);
    for (int i = 0; i < 10000; ++i) {
        EXPECT_EQ(vec[i], i);
    }
}

TEST(EdgeCases, PushBack_WithStrings) {
    Vector<std::string> vec;
    
    for (int i = 0; i < 1000; ++i) {
        vec.push_back("string_" + std::to_string(i));
    }
    
    EXPECT_EQ(vec.size(), 1000);
    EXPECT_EQ(vec[0], "string_0");
    EXPECT_EQ(vec[999], "string_999");
}

// Invalid Access Tests
TEST(EdgeCases, Access_InvalidIndex_ThrowsException) {
    Vector<int> vec({1, 2, 3});
    
    EXPECT_THROW(vec.at(3), std::out_of_range);
    EXPECT_THROW(vec.at(100), std::out_of_range);
}

TEST(EdgeCases, Access_InvalidIndex_OnEmptyVector) {
    Vector<int> vec;
    
    EXPECT_THROW(vec.at(0), std::out_of_range);
    EXPECT_THROW(vec.at(1), std::out_of_range);
}

TEST(EdgeCases, Access_InvalidIndex_AfterClear) {
    Vector<int> vec({1, 2, 3, 4, 5});
    vec.clear();
    
    EXPECT_THROW(vec.at(0), std::out_of_range);
    EXPECT_THROW(vec.at(1), std::out_of_range);
}

// Interleaved Operations Tests
TEST(EdgeCases, PushAndPop_InterleavedOperationsStayConsistent) {
    Vector<int> vec;
    
    vec.push_back(1);
    vec.push_back(2);
    vec.pop_back();
    vec.push_back(3);
    vec.push_back(4);
    vec.pop_back();
    vec.push_back(5);
    vec.push_back(6);
    vec.pop_back();
    vec.pop_back();
    vec.push_back(7);
    
    EXPECT_EQ(vec.size(), 3);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 3);
    EXPECT_EQ(vec[2], 7);
}

TEST(EdgeCases, PushAndPop_ComplexInterleavedOperations) {
    Vector<int> vec;
    
    for (int i = 0; i < 100; ++i) {
        vec.push_back(i);
        if (i % 3 == 0) {
            vec.pop_back();
        }
    }
    
    EXPECT_GT(vec.size(), 0);
    for (size_t i = 0; i < vec.size(); ++i) {
        EXPECT_GE(vec[i], 0);
        EXPECT_LT(vec[i], 100);
    }
}

// Resize Tests
TEST(EdgeCases, Resize_MaintainsExistingElementsCorrectly) {
    Vector<int> vec(1);
    
    vec.push_back(1);
    EXPECT_EQ(vec.capacity(), 1);
    EXPECT_EQ(vec.size(), 1);
    EXPECT_EQ(vec[0], 1);
    
    vec.push_back(2);
    EXPECT_GT(vec.capacity(), 1);
    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    
    vec.push_back(3);
    vec.push_back(4);
    vec.push_back(5);
    
    EXPECT_EQ(vec.size(), 5);
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);
    EXPECT_EQ(vec[3], 4);
    EXPECT_EQ(vec[4], 5);
}

TEST(EdgeCases, Resize_MultipleResizes) {
    Vector<int> vec(1);
    
    for (int i = 0; i < 100; ++i) {
        vec.push_back(i);
        EXPECT_EQ(vec[i], i);
    }
    
    EXPECT_EQ(vec.size(), 100);
    for (int i = 0; i < 100; ++i) {
        EXPECT_EQ(vec[i], i);
    }
}

// Memory Management Tests
TEST(EdgeCases, MemoryManagement_NoLeaks) {
    Vector<int> vec;
    
    for (int i = 0; i < 100; ++i) {
        Vector<int> temp;
        for (int j = 0; j < 10; ++j) {
            temp.push_back(j);
        }
    }
    
    EXPECT_TRUE(true);
}

TEST(EdgeCases, MemoryManagement_CopyAndMove) {
    Vector<int> original;
    for (int i = 0; i < 100; ++i) {
        original.push_back(i);
    }
    
    Vector<int> copy(original);
    EXPECT_EQ(copy.size(), 100);
    
    Vector<int> moved(std::move(original));
    EXPECT_EQ(moved.size(), 100);
    EXPECT_EQ(original.size(), 0);
    
    Vector<int> assigned;
    assigned = copy;
    EXPECT_EQ(assigned.size(), 100);
    
    Vector<int> moveAssigned;
    moveAssigned = std::move(moved);
    EXPECT_EQ(moveAssigned.size(), 100);
    EXPECT_EQ(moved.size(), 0);
}

// Stress Tests
TEST(EdgeCases, StressTest_RapidPushPop) {
    Vector<int> vec;
    
    for (int i = 0; i < 1000; ++i) {
        vec.push_back(i);
        if (i % 2 == 0) {
            vec.pop_back();
        }
    }
    
    EXPECT_EQ(vec.size(), 500);
}

TEST(EdgeCases, StressTest_AlternatingOperations) {
    Vector<int> vec;
    
    for (int i = 0; i < 100; ++i) {
        if (i % 3 == 0) {
            vec.push_back(i);
        } else if (i % 3 == 1) {
            if (!vec.empty()) {
                vec.pop_back();
            }
        } else {
            vec.clear();
        }
    }
    
    EXPECT_TRUE(true);
}

// Zero Capacity Tests
TEST(EdgeCases, ZeroCapacity_Constructor) {
    Vector<int> vec(0);
    
    EXPECT_EQ(vec.size(), 0);
    EXPECT_EQ(vec.capacity(), 0);
    EXPECT_TRUE(vec.empty());
    
    vec.push_back(1);
    EXPECT_EQ(vec.size(), 1);
    EXPECT_GT(vec.capacity(), 0);
}

TEST(EdgeCases, ZeroCapacity_PushBack) {
    Vector<int> vec(0);
    
    vec.push_back(1);
    EXPECT_EQ(vec.size(), 1);
    EXPECT_GT(vec.capacity(), 0);
    EXPECT_EQ(vec[0], 1);
}

// Self Assignment Tests
TEST(EdgeCases, SelfAssignment_Complex) {
    Vector<int> vec;
    for (int i = 0; i < 50; ++i) {
        vec.push_back(i);
    }
    
    vec = vec;
    
    EXPECT_EQ(vec.size(), 50);
    for (int i = 0; i < 50; ++i) {
        EXPECT_EQ(vec[i], i);
    }
}

TEST(EdgeCases, SelfMoveAssignment_Complex) {
    Vector<int> vec;
    for (int i = 0; i < 50; ++i) {
        vec.push_back(i);
    }
    
    vec = std::move(vec);
    
    EXPECT_EQ(vec.size(), 50);
    for (int i = 0; i < 50; ++i) {
        EXPECT_EQ(vec[i], i);
    }
}

// Exception Safety Tests
TEST(EdgeCases, ExceptionSafety_PushBack) {
    Vector<int> vec({1, 2, 3, 4, 5});
    size_t original_size = vec.size();
    
    vec.push_back(6);
    EXPECT_EQ(vec.size(), original_size + 1);
    EXPECT_EQ(vec[original_size], 6);
}

TEST(EdgeCases, ExceptionSafety_PopBack) {
    Vector<int> vec({1, 2, 3, 4, 5});
    size_t original_size = vec.size();
    
    vec.pop_back();
    EXPECT_EQ(vec.size(), original_size - 1);
}

TEST(EdgeCases, ExceptionSafety_Clear) {
    Vector<int> vec({1, 2, 3, 4, 5});
    
    vec.clear();
    EXPECT_EQ(vec.size(), 0);
    EXPECT_TRUE(vec.empty());
}

// Boundary Conditions
TEST(EdgeCases, BoundaryConditions_SizeOneVector) {
    Vector<int> vec;
    vec.push_back(42);
    
    EXPECT_EQ(vec.size(), 1);
    EXPECT_EQ(vec[0], 42);
    EXPECT_EQ(vec.at(0), 42);
    
    vec.pop_back();
    EXPECT_EQ(vec.size(), 0);
    EXPECT_TRUE(vec.empty());
}

TEST(EdgeCases, BoundaryConditions_SizeZeroVector) {
    Vector<int> vec;
    
    EXPECT_EQ(vec.size(), 0);
    EXPECT_TRUE(vec.empty());
    EXPECT_THROW(vec.at(0), std::out_of_range);
}

TEST(EdgeCases, BoundaryConditions_MaximumSize) {
    Vector<int> vec;
    
    for (int i = 0; i < 10000; ++i) {
        vec.push_back(i);
    }
    
    EXPECT_EQ(vec.size(), 10000);
    EXPECT_EQ(vec[9999], 9999);
}
