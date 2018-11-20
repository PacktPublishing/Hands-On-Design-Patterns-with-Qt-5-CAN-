#include <gtest/gtest.h>
#include <QtCore>
#include <QApplication>
#include <QStringListModel>
#include <QFileSystemModel>

TEST(Chapter11, accessQStringListModelByModelIndex) {
    auto list = QStringList{"1", "2", "3", "4"};
    auto model = new QStringListModel();
    model->setStringList(list);

    int row = 0;
    QModelIndex index = model->index(row);
    QVariant data = model->data(index);

    ASSERT_EQ(data.toString(), QString("1"));

    delete model;
}

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    Q_UNUSED(app);

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
