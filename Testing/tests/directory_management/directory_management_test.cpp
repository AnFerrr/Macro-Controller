#include "gtest/gtest.h"

class DirectoryTest : public ::testing::Test
{
protected:
    void SetUp() override {
        int a = 0;
    }
};

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}