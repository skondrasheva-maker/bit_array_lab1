#include <gtest/gtest.h>
#include "BitArray.h"
#include <stdexcept>

TEST(BitArraySmokeTest, EnvironmentWorks) {
    BitArray array;
    SUCCEED();
}

TEST(BitArrayTest, BasicConstructorsAndSize) {
    BitArray empty;
    EXPECT_EQ(empty.size(), 0);
    EXPECT_TRUE(empty.empty());
    BitArray a(10, 5);
    EXPECT_EQ(a.size(), 10);
    EXPECT_FALSE(a.empty());

    BitArray b(a);
    EXPECT_EQ(b.size(), 10);

    EXPECT_EQ(b[0], true);  // 5 = 101, 0-й бит = 1
    EXPECT_EQ(b[1], false); // 1-й бит = 0
    EXPECT_EQ(b[2], true);  // 2-й бит = 1

    BitArray c;
    c = a;
    EXPECT_EQ(c.size(), 10);
    EXPECT_EQ(c[2], true);
}

TEST(BitArrayTest, OperatorBracketAndExceptions) {
    BitArray a(5, 3); // 3 = 011 

    EXPECT_EQ(a[0], true);  // 1
    EXPECT_EQ(a[1], true);  // 1
    EXPECT_EQ(a[2], false); // 0

    EXPECT_THROW(a[-1], std::out_of_range);
    EXPECT_THROW(a[5], std::out_of_range);
    EXPECT_THROW(a[100], std::out_of_range);
}

TEST(BitArrayTest, ClearMethod) {
    BitArray a(10, 255);
    EXPECT_EQ(a.size(), 10);

    a.clear(); 

    EXPECT_EQ(a.size(), 0);
    EXPECT_TRUE(a.empty());
}

TEST(BitArrayTest, PushBackMethod) {
    BitArray a;

    a.push_back(true);
    a.push_back(false);
    a.push_back(true);

    EXPECT_EQ(a.size(), 3);
    EXPECT_EQ(a[0], true);
    EXPECT_EQ(a[1], false);
    EXPECT_EQ(a[2], true);

    for (int i = 0; i < 62; ++i) {
        a.push_back(false);
    }
    EXPECT_EQ(a.size(), 65);
    EXPECT_EQ(a[64], false);
}

TEST(BitArrayTest, ResizeMethod) {
    BitArray a(10, 1023); //1023 = 1111111111
    a.resize(5);
    EXPECT_EQ(a.size(), 5);
    for (int i = 0; i < 5; ++i) {
        EXPECT_EQ(a[i], true);
    }
    a.resize(8);
    EXPECT_EQ(a.size(), 8);
    EXPECT_EQ(a[5], false);
    EXPECT_EQ(a[7], false);

    BitArray b(4, 0);
    b.resize(8, true);
    EXPECT_EQ(b.size(), 8);
    EXPECT_EQ(b[0], false); 
    EXPECT_EQ(b[4], true); 
    EXPECT_EQ(b[7], true);

    EXPECT_THROW(b.resize(-5), std::invalid_argument);
}