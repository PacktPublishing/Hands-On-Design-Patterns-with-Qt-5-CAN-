
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "primefactors.h"
#include <list>

using namespace testing;

TEST(PrimeFactors, oneShouldReturnEmpty)
{
    ASSERT_THAT(getFactors(1), std::list<int>{} );
}

