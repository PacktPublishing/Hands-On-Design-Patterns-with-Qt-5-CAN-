#include <QApplication>
#include <QtCore>
#include <QListView>
#include <QStringListModel>
#include <QFileSystemModel>
#include <QTableView>
#include <QTreeView>

int QStringListModelAndQListView(int argc, char *argv[]) {
    QApplication app(argc, argv);

    auto model = new QStringListModel(&app);
    auto nameList = QStringList{"Oliver", "Jack	", "Harry", "Jacob" ,"Charlie", "Thomas", "George", "Oscar", "James", "William"};
    model->setStringList(nameList);

    auto view = new QListView();
    view->setModel(model);
    view->show();

    return app.exec();
}

int QStringListModelAndQTableView(int argc, char *argv[]) {
    QApplication app(argc, argv);

    auto model = new QStringListModel(&app);
    auto nameList = QStringList{"Oliver", "Jack	", "Harry", "Jacob" ,"Charlie", "Thomas", "George", "Oscar", "James", "William"};
    model->setStringList(nameList);

    auto view = new QTableView();
    view->setModel(model);
    view->show();

    return app.exec();
}

int QFileSystModelAndQTreeView(int argc, char *argv[]) {
    QApplication app(argc, argv);

    auto model = new QFileSystemModel(&app);
    model->setRootPath(SRCDIR);

    auto view = new QTableView();
    view->setModel(model);
    view->setRootIndex(model->index(SRCDIR));
    view->show();

    return app.exec();
}

int main(int argc, char *argv[])
{
    return QFileSystModelAndQTreeView(argc, argv);
}
