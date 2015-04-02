#include "HelloWorld.h"
#include "gtest/gtest.h"

TEST(SampleTest, Equality) {
    HelloWorld hw;
    EXPECT_EQ(hw.getHelloWorld(), "Hello World!");
}

