#include "gtest/gtest.h"

TEST(TestSuiteName, TestName) {
    EXPECT_EQ(4, 4);
    EXPECT_EQ(5 - 1, 3 + 1);
    EXPECT_NE(4, 44);
}

TEST(TestSuiteName, TestName2) {
    EXPECT_NEAR(10.0 / 3.0, 3.33333333, 0.0001);
    EXPECT_EQ("123", std::to_string(123));
}