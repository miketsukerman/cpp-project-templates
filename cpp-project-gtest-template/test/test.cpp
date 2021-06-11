#include <gtest/gtest.h>
#include "sample.h"

TEST(SampleObject, sum) {

    SampleObject sm;

    EXPECT_EQ (sm.sum(2,2),  4);
}