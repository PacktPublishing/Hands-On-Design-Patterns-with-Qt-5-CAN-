#include <QSpinBox>
#include <QPainter>
#include <QtCore>
#include "studentinfodelegate.h"

StudentInfoDelegate::StudentInfoDelegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

QWidget *StudentInfoDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    bool isStudentAgeField = index.internalId() > 0 && index.column() == 2;
    if (isStudentAgeField) {
        QSpinBox *editor = new QSpinBox(parent);
        return editor;
    } else {
        return QStyledItemDelegate::createEditor(parent, option, index);
    }
}

void StudentInfoDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    bool isStudentAgeField = index.internalId() > 0 && index.column() == 2;
    if (isStudentAgeField) {
        int value = index.model()->data(index, Qt::EditRole).toInt();
        QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
        spinBox->setValue(value);
    } else {
        return QStyledItemDelegate::setEditorData(editor, index);
    }
}

void StudentInfoDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    bool isStudentAgeField = index.internalId() > 0 && index.column() == 2;
    if (isStudentAgeField) {
        QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
        spinBox->interpretText();
        int value = spinBox->value();
        model->setData(index, value, Qt::EditRole);
    } else {
        return QStyledItemDelegate::setModelData(editor, model, index);
    }
}

void StudentInfoDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
