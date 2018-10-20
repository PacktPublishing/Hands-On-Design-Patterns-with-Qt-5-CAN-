#include <QCoreApplication>
#include <gtest/gtest.h>

template <typename T>
struct has_squeeze {

    template <typename Type>
    static inline auto test(int) -> typename std::enable_if<std::is_same<decltype(std::declval<Type>().squeeze()), void>::value, std::true_type>::type;

    template <typename>
    static inline auto test(...) -> std::false_type;

    enum {
        value = std::is_same<decltype(test<T>(0)), std::true_type>::value
    };
};

TEST(Chapter07, has_squeeze) {
    ASSERT_EQ(has_squeeze<std::string>::value,  0);
    ASSERT_EQ(has_squeeze<QString>::value,      1);
}

int main(int argc, char** argv) {

    QCoreApplication app(argc, argv);
    Q_UNUSED(app);

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
