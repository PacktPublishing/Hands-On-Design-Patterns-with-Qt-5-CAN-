#include <QPainter>
#include <QFontMetrics>
#include "schoolclassinfodelegate.h"

SchoolClassInfoDelegate::SchoolClassInfoDelegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

void SchoolClassInfoDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if (option.state & QStyle::State_Selected)
        painter->fillRect(option.rect, option.palette.highlight());

    auto className = index.data().toString();
    auto displayText =  QString("Class: %1").arg(className);
    auto toplLeft = option.rect.topLeft() + QPointF(10,20);
    painter->drawText(toplLeft, displayText);
}

QSize SchoolClassInfoDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(48, 48);
}
