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

TEST(IncrementTest, ValueWithDivider) {
    Increment<int> increment;
    increment.setDivider(4);
    ASSERT_EQ(0, increment.value());
    ASSERT_EQ(false, increment.hasChanged());

    increment.set(1);
    ASSERT_EQ(0, increment.value());
    ASSERT_EQ(false, increment.hasChanged());
    increment.set(1);
    ASSERT_EQ(0, increment.value());
    ASSERT_EQ(false, increment.hasChanged());
    increment.set(1);
    ASSERT_EQ(0, increment.value());
    ASSERT_EQ(false, increment.hasChanged());
    increment.set(1);
    ASSERT_EQ(1, increment.value());
    ASSERT_EQ(true, increment.hasChanged());
    increment.set(1);
    ASSERT_EQ(1, increment.value());
    ASSERT_EQ(true, increment.hasChanged());
    increment.set(1);
    ASSERT_EQ(1, increment.value());
    ASSERT_EQ(true, increment.hasChanged());
    increment.set(1);
    ASSERT_EQ(1, increment.value());
    ASSERT_EQ(true, increment.hasChanged());
    increment.set(1);
    ASSERT_EQ(2, increment.value());
    ASSERT_EQ(true, increment.hasChanged());

    increment.set(1);
    ASSERT_EQ(2, increment.value());
    ASSERT_EQ(true, increment.hasChanged());
    increment.set(1);
    ASSERT_EQ(2, increment.value());
    ASSERT_EQ(true, increment.hasChanged());

    increment.resetState();
    ASSERT_EQ(0, increment.value());
    ASSERT_EQ(false, increment.hasChanged());
    increment.set(1);
    ASSERT_EQ(0, increment.value());
    ASSERT_EQ(false, increment.hasChanged());
    increment.set(1);
    ASSERT_EQ(1, increment.value());
    ASSERT_EQ(true, increment.hasChanged());
}

TEST(IncrementTest, NegativeValueWithDivider) {
    Increment<int> increment;
    increment.setDivider(4);
    ASSERT_EQ(0, increment.value());
    ASSERT_EQ(false, increment.hasChanged());

    increment.set(-1);
    ASSERT_EQ(0, increment.value());
    ASSERT_EQ(false, increment.hasChanged());
    increment.set(-1);
    ASSERT_EQ(0, increment.value());
    ASSERT_EQ(false, increment.hasChanged());
    increment.set(-1);
    ASSERT_EQ(0, increment.value());
    ASSERT_EQ(false, increment.hasChanged());
    increment.set(-1);
    ASSERT_EQ(-1, increment.value());
    ASSERT_EQ(true, increment.hasChanged());
    increment.set(-1);
    ASSERT_EQ(-1, increment.value());
    ASSERT_EQ(true, increment.hasChanged());
    increment.set(-1);
    ASSERT_EQ(-1, increment.value());
    ASSERT_EQ(true, increment.hasChanged());
    increment.set(-1);
    ASSERT_EQ(-1, increment.value());
    ASSERT_EQ(true, increment.hasChanged());
    increment.set(-1);
    ASSERT_EQ(-2, increment.value());
    ASSERT_EQ(true, increment.hasChanged());

    increment.set(-1);
    ASSERT_EQ(-2, increment.value());
    ASSERT_EQ(true, increment.hasChanged());
    increment.set(-1);
    ASSERT_EQ(-2, increment.value());
    ASSERT_EQ(true, increment.hasChanged());

    increment.resetState();
    ASSERT_EQ(0, increment.value());
    ASSERT_EQ(false, increment.hasChanged());
    increment.set(-1);
    ASSERT_EQ(0, increment.value());
    ASSERT_EQ(false, increment.hasChanged());
    increment.set(-1);
    ASSERT_EQ(-1, increment.value());
    ASSERT_EQ(true, increment.hasChanged());
}