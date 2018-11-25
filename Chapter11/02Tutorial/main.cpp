#include <QApplication>
#include <QHBoxLayout>
#include <QListView>
#include <QTableView>
#include <QTreeView>
#include <QtCore>
#include "schoolclassmodel.h"
#include "studentinfodelegate.h"
#include "schoolclassinfodelegate.h"

static QList<SchoolClassInfo> mockData {
    {
        "1A",{
            {"001", "Rodger", 16},
            {"002", "Lino", 17},
        },
    },
    {
        "1B", {
            {"005", "Marx", 16},
        }
    },
    {
        "1C", {}
    }
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    auto model = new SchoolClassModel(&app);
    model->setStorage(mockData);

    auto *window = new QWidget;

    auto listView = new QListView(window);
    listView->setModel(model);
    listView->setItemDelegate(new SchoolClassInfoDelegate());

    auto tableView = new QTableView(window);
    tableView->setModel(model);
    tableView->setRootIndex(model->index(0,0));
    tableView->setItemDelegate(new StudentInfoDelegate());

    auto treeView = new QTreeView(window);
    treeView->setModel(model);

    auto *layout = new QHBoxLayout(window);
    layout->addWidget(listView);
    layout->addWidget(tableView);
    layout->addWidget(treeView);

    window->show();

    return app.exec();
}
