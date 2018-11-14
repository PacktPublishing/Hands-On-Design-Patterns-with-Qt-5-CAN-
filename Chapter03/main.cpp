#include <gtest/gtest.h>
#include <QList>
#include <QVariantMap>
#include <QtConcurrent>
#include <math.h>
#include <list>
#include <memory>

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

    auto isChanged = [&](const Foo arg) {
        auto before = arg.bar;
        inc();
        auto after = arg.bar;
        return before != after;
    };

    ASSERT_EQ(isChanged(foo), false);
}

TEST(Chapter03, copy_on_write) {
    class Foo {
    public:
        int bar = 0;
    };

    class SharedFoo {
    public:
        SharedFoo() : data(new Foo) {
        }

        void setBar(int value) {
            if (data.use_count() != 1) {
                Foo* foo = new Foo(*data.get());
                data.reset(foo);
            }
            data->bar = value;
        }

        int bar() const {
            return data->bar;
        }

        bool isSharedWith(const SharedFoo &rhs) {
            return data.get() == rhs.data.get();
        }

        std::shared_ptr<Foo> data;
    };

    SharedFoo foo1, foo2;
    foo1.setBar(99);
    foo2 = foo1;

    ASSERT_EQ(foo1.bar(),              foo2.bar());
    ASSERT_EQ(foo1.data.use_count(),   2);
    ASSERT_EQ(foo2.data.use_count(),   2);
    ASSERT_EQ(foo1.isSharedWith(foo2), true);

    foo2.setBar(100);

    ASSERT_EQ(foo1.bar(),              99);
    ASSERT_EQ(foo2.bar(),              100);
    ASSERT_EQ(foo1.data.use_count(),   1);
    ASSERT_EQ(foo2.data.use_count(),   1);
    ASSERT_EQ(foo1.isSharedWith(foo2), false);
}

TEST(Chapter03, qt_immutable_classes) {
    QList<int> a{1,2,3};
    QList<int> b{1,2,3};
    QList<int> c = a;

    ASSERT_EQ( a == b,            true);
    ASSERT_EQ( a.isSharedWith(b), false);

    ASSERT_EQ( a == c,            true);
    ASSERT_EQ( a.isSharedWith(c), true);
}

TEST(Chapter03, using_immutable_object_in_thread) {
    QMap<QString,int> source = {{"value1", 1}, {"value2", 2}};

    auto worker = [source]() {
        // @ A Thread in the Thread Pool
        auto localCopy = source;
        localCopy["value2"] = 9;

        ASSERT_EQ(source["value1"]+source["value2"],        3); // Point B
        ASSERT_EQ(localCopy["value1"]+localCopy["value2"],  10);
    };

    // @ Main Thread
    QFuture<void> future = QtConcurrent::run(worker);
    source["value1"] = 3;  // Point A
    future.waitForFinished();

    ASSERT_EQ(source["value1"]+source["value2"],  5);
}

int main(int argc, char** argv) {
    QCoreApplication app(argc, argv);
    Q_UNUSED(app);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
