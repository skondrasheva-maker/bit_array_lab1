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
    EXPECT_EQ(b[1], false); 
    EXPECT_EQ(b[2], true); 

    BitArray c;
    c = a;
    EXPECT_EQ(c.size(), 10);
    EXPECT_EQ(c[2], true);
}

TEST(BitArrayTest, OperatorBracketAndExceptions) {
    BitArray a(5, 3); // 3 = 011 

    EXPECT_EQ(a[0], true);  
    EXPECT_EQ(a[1], true);  
    EXPECT_EQ(a[2], false); 

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

TEST(BitArrayTest, SetBit) {
    BitArray a(10, 0);

    a.set(3, true);
    EXPECT_EQ(a[3], true);
    EXPECT_EQ(a.count(), 1);

    a.set(3, false);
    EXPECT_EQ(a[3], false);
    EXPECT_EQ(a.count(), 0);

    a.set(0, true).set(2, true).set(4, true);
    EXPECT_EQ(a.count(), 3);
    EXPECT_EQ(a[0], true);
    EXPECT_EQ(a[2], true);
    EXPECT_EQ(a[4], true);

    EXPECT_THROW(a.set(-1, true), std::out_of_range);
    EXPECT_THROW(a.set(10, true), std::out_of_range);
}

TEST(BitArrayTest, SetAll) {
    BitArray a(10, 0); 

    a.set(); 

    EXPECT_EQ(a.count(), 10); 
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(a[i], true);
    }

    BitArray b(100, 0);
    b.set();
    EXPECT_EQ(b.count(), 100);
}

TEST(BitArrayTest, ResetBit) {
    BitArray a(10, 1023); 

    a.reset(5);
    EXPECT_EQ(a[5], false);
    EXPECT_EQ(a.count(), 9);

    a.reset(0).reset(2).reset(4);
    EXPECT_EQ(a.count(), 6);
    EXPECT_EQ(a[0], false);
    EXPECT_EQ(a[2], false);
    EXPECT_EQ(a[4], false);

    EXPECT_THROW(a.reset(-1), std::out_of_range);
    EXPECT_THROW(a.reset(10), std::out_of_range);
}

TEST(BitArrayTest, ResetAll) {
    BitArray a(10, 1023); 

    a.reset(); 

    EXPECT_EQ(a.count(), 0);
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(a[i], false);
    }
}

TEST(BitArrayTest, AnyMethod) {
    BitArray a(10, 0); 
    EXPECT_FALSE(a.any());

    a.set(5, true);
    EXPECT_TRUE(a.any());

    BitArray b(10, 1023); 
    EXPECT_TRUE(b.any());

    BitArray empty;
    EXPECT_FALSE(empty.any());
}

TEST(BitArrayTest, NoneMethod) {
    BitArray a(10, 0); 
    EXPECT_TRUE(a.none());

    a.set(5, true);
    EXPECT_FALSE(a.none());

    BitArray b(10, 1023);
    EXPECT_FALSE(b.none());

    BitArray empty;
    EXPECT_TRUE(empty.none());
}

TEST(BitArrayTest, InversionOperator) {
    BitArray a(10, 0); 

    BitArray b = ~a; 

    EXPECT_EQ(b.count(), 10); 
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(b[i], true);
    }

    EXPECT_EQ(a.count(), 0);

    BitArray c(5, 5); 
    BitArray d = ~c;

    EXPECT_EQ(d[0], false); 
    EXPECT_EQ(d[1], true);  
    EXPECT_EQ(d[2], false); 
    EXPECT_EQ(d[3], true);  
    EXPECT_EQ(d[4], true);  
}

TEST(BitArrayTest, CountMethod) {
    BitArray a(10, 0);
    EXPECT_EQ(a.count(), 0);

    a.set(0, true).set(3, true).set(7, true);
    EXPECT_EQ(a.count(), 3);

    BitArray b(10, 1023); 
    EXPECT_EQ(b.count(), 10);

    BitArray empty;
    EXPECT_EQ(empty.count(), 0);

    BitArray c(100, 0);
    for (int i = 0; i < 100; i += 2) {
        c.set(i, true);
    }
    EXPECT_EQ(c.count(), 50);
}