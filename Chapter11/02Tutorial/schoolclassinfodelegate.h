#pragma once
#include <QObject>
#include <QStyledItemDelegate>

class SchoolClassInfoDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit SchoolClassInfoDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
                               const QModelIndex &index) const;

    QSize sizeHint(const QStyleOptionViewItem &option,
                      const QModelIndex &index) const;

private:
    int padding = 10;
};

