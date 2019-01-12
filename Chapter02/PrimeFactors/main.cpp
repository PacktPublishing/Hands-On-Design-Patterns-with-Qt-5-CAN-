//#include "tst_testproject.h"

#include <gtest/gtest.h>
#include <iostream>
#include <any>

int main(int argc, char *argv[])
{
    std::any a = 1;
    int b = std::any_cast<int>(a);
    std::cout << "Test: " << b << std::endl;
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
