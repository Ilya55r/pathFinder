#include "wallitem.h"
#include <QPainter>
#include "helper.h"

const int PADDING = 5;
const int BRICK_CELL_W = 3;

WallItem::WallItem(QGraphicsItem *parent) : QGraphicsRectItem(parent)
{

}

void WallItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->save();
    painter->fillRect(QRect(PADDING, PADDING, Helper::ITEM_SIZE - 2 * PADDING, Helper::ITEM_SIZE - 2 * PADDING), QColor(180, 70, 34));
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(2);
    painter->setPen(pen);
    painter->drawRect(QRect(PADDING, PADDING, Helper::ITEM_SIZE - 2 * PADDING, Helper::ITEM_SIZE - 2 * PADDING));
    int step = (Helper::ITEM_SIZE - 2 * PADDING) / BRICK_CELL_W;
    for (int i = 0; i < Helper::ITEM_SIZE - 2 * PADDING; i+=step){
        painter->drawLine(QPointF(PADDING, PADDING + i), QPoint(Helper::ITEM_SIZE - PADDING, PADDING + i));
    }
    painter->restore();
}
