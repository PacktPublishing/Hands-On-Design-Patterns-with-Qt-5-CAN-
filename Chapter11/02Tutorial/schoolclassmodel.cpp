#include <QMetaProperty>
#include <QtCore>
#include "schoolclassmodel.h"

SchoolClassModel::SchoolClassModel(QObject *parent) : QAbstractItemModel(parent)
{

}

QModelIndex SchoolClassModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!parent.isValid()) {
        return createIndex(row, column,
                           static_cast<quintptr>(0));
    } else if (parent.internalId() == 0){
        return createIndex(row, column,
                           static_cast<quintptr>(parent.row() + 1));
    } else {
        return QModelIndex();
    }
}

QModelIndex SchoolClassModel::parent(const QModelIndex &child) const
{
    if (!child.isValid()) {
        return QModelIndex();
    }

    auto internalId = static_cast<int>(child.internalId());
    if (internalId == 0) {
        return QModelIndex();
    }

    auto parentRow = internalId - 1;
    return index(parentRow, 0);
}

QVariant SchoolClassModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (role != Qt::DisplayRole && role != Qt::EditRole) {
        return QVariant();
    }

    auto internalId = index.internalId();

    if (internalId == 0) {
        return m_storage[index.row()].className;
    } else {
        auto parentIndex = parent(index);
        auto& studentList = m_storage[parentIndex.row()].students;
        return studentList[index.row()].name;
    }
}

int SchoolClassModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return 1;
}

int SchoolClassModel::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid()) {
        return m_storage.size();
    }

    if (parent.internalId() == 0) {
        auto& studentList = m_storage[parent.row()].students;
        return studentList.size();
    }

    return 0;
}

QVariant SchoolClassModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    if (orientation == Qt::Horizontal && section == 0 ) {
        return QObject::tr("Student");
    }

    return QVariant();
}

void SchoolClassModel::setStorage(const QList<SchoolClassInfo> &storage)
{
    beginResetModel();
    m_storage = storage;
    endResetModel();
}
