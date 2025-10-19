#include "pathitem.h"
#include <QPainter>
#include "helper.h"
PathItem::PathItem(const QSize &size, const QList<QPoint> &points) :
    QGraphicsItem(), size_(size), points_(points)
{

}

QRectF PathItem::boundingRect() const
{
    return QRectF(0, 0, size_.width(), size_.height());
}

void PathItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->save();
    QPen pen;
    pen.setStyle(Qt::DotLine);
    pen.setColor(Qt::red);
    pen.setWidth(3);
    painter->setPen(pen);
    for (int i = 1; i < points_.size(); i++){
        QPoint realPoint1 = points_[i - 1] * Helper::ITEM_SIZE;
        realPoint1 -= QPoint(Helper::ITEM_SIZE / 2, Helper::ITEM_SIZE / 2);
        QPoint realPoint2 = points_[i] * Helper::ITEM_SIZE;
        realPoint2 -= QPoint(Helper::ITEM_SIZE / 2, Helper::ITEM_SIZE / 2);
        painter->drawLine(realPoint1, realPoint2);
    }
    painter->restore();
}
