#include <QApplication>
#include <QListView>
#include <QTableView>
#include <QTreeView>
#include <QtCore>
#include "mainwindow.h"
#include "schoolclassmodel.h"

static QList<SchoolClassInfo> mockData {
    {
        "1A",{
            {"001", "Rodger", StudentInfo::Male},
            {"002", "Lino", StudentInfo::Male},
        },
    },
    {
        "1B", {
            {"005", "Marx", StudentInfo::Female},
        }
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    auto model = new SchoolClassModel(&a);
    model->setStorage(mockData);

    QTreeView treeView;
    treeView.setModel(model);
    treeView.show();

    QTableView tableView;
    tableView.setModel(model);
    tableView.setRootIndex(model->index(0,0));
    tableView.show();

    QListView listView;
    listView.setModel(model);
    listView.show();

    return a.exec();
}
