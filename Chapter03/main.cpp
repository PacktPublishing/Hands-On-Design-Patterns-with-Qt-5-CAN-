#include <gtest/gtest.h>
#include <math.h>
#include <list>

TEST(Chapter03, const_reference_is_not_immutable) {
    class Foo {
    public:
        int bar = 0;
    };

    Foo foo;

    auto inc = [&]() {
        foo.bar++;
    };

    auto isChanged = [&](const Foo& arg) {
        auto before = arg.bar;
        inc();
        auto after = arg.bar;
        return before != after;
    };

    ASSERT_EQ(isChanged(foo), true);
}

TEST(Chapter03, defentive_copy) {
    class Foo {
    public:
        int bar = 0;
    };

    Foo foo;

    auto inc = [&]() {
        foo.bar++;
    };

    auto isChanged = [&](Foo arg) {
        auto before = arg.bar;
        inc();
        auto after = arg.bar;
        return before != after;
    };

    ASSERT_EQ(isChanged(foo), false);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
