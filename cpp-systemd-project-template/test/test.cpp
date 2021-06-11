#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "sample.h"

SCENARIO("testcase", "")
{
    GIVEN("usercase 2+2")
    {
        SampleObject sm;

        WHEN("instance is created")
        {
            THEN("test sum(2,2)")
            {
                REQUIRE(sm.sum({2,2}) == 4);
            }
        }
    }
}
