
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "primefactors.h"
#include <list>

using namespace testing;

TEST(PrimeFactors, oneShouldReturnEmpty)
{
    ASSERT_THAT(getFactors(1), std::list<int>{} );
}

TEST(PrimeFactors, twoShouldReturnTwo)
{
    ASSERT_THAT(getFactors(2), std::list<int>{2});
}

TEST(PrimeFactors, fourShouldReturnTwoTwo)
{
    ASSERT_THAT(getFactors(4), (std::list<int>{2,2}));
}
