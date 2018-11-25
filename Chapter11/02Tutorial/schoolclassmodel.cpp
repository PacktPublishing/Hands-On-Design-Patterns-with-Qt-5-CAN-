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
        auto& student = studentList[index.row()];

        switch (index.column()) {
        case 0:
            return student.name;
        case 1:
            return student.studentId;
        case 2:
            return student.age;
        }
    }

    return QVariant();
}

bool SchoolClassModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!index.isValid() || role != Qt::EditRole || index.internalId() == 0) {
        return false;
    }

    auto parentIndex = parent(index);
    auto& studentList = m_storage[parentIndex.row()].students;
    auto& student = studentList[index.row()];
    switch (index.column()) {
    case 0:
        student.name = value.toString();
        break;
    case 1:
        student.studentId = value.toString();
        break;
    case 2:
        student.age = value.toInt();
        break;
    }

    emit dataChanged(index, index, {role});
    return true;
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

int SchoolClassModel::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid()) {
        return 1;
    }

    if (parent.internalId() == 0) {
        return 3;
    }

    return 0;
}

QVariant SchoolClassModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QObject::tr("Student");
        case 1:
            return QObject::tr("ID");
        case 2:
            return QObject::tr("Age");
        }
    }

    return QVariant();
}

Qt::ItemFlags SchoolClassModel::flags(const QModelIndex &index) const
{
    if (!index.isValid() || index.internalId() == 0) {
        return Qt::NoItemFlags;
    }

    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

void SchoolClassModel::setStorage(const QList<SchoolClassInfo> &storage)
{
    beginResetModel();
    m_storage = storage;
    endResetModel();
}
