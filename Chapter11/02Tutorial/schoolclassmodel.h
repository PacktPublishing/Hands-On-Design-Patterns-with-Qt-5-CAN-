#pragma once
#include <QObject>
#include <QAbstractItemModel>
#include "studentinfo.h"
#include "schoolclassinfo.h"

class SchoolClassModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit SchoolClassModel(QObject *parent = nullptr);

    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const;

    QModelIndex parent(const QModelIndex &child) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    int columnCount(const QModelIndex &parent = QModelIndex()) const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    void setStorage(const QList<SchoolClassInfo> &storage);

private:
    QList<SchoolClassInfo> m_storage;
};
