#include <gtest/gtest.h>
#include "FpIncrement.h"

using namespace fp;

TEST(IncrementTest, State) {
    Increment<int> increment;
    ASSERT_EQ(false, increment.hasChanged());
    increment.resetState();
    ASSERT_EQ(false, increment.hasChanged());
    increment.set(4);
    ASSERT_EQ(true, increment.hasChanged());
}

TEST(IncrementTest, Value) {
    Increment<int> increment;
    ASSERT_EQ(0, increment.value());
    increment.set(4);
    ASSERT_EQ(4, increment.value());
    increment.set(4);
    ASSERT_EQ(8, increment.value());
    increment.resetState();
    ASSERT_EQ(0, increment.value());
}


