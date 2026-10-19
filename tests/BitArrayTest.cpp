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