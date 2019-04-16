#include <gtest/gtest.h>
#include "FpValue.h"

using namespace fp;

TEST(ValueTest, State) {
    Value<int> value;
    ASSERT_EQ(false, value.hasChanged());
    value.resetState();
    ASSERT_EQ(false, value.hasChanged());
    value.set(4);
    ASSERT_EQ(true, value.hasChanged());
}

TEST(ValueTest, Value) {
    Value<int> value;
    ASSERT_EQ(0, value.value());
    value.set(4);
    ASSERT_EQ(4, value.value());
}


