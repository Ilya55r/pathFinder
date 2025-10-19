#include "gridview.h"
#include <QWheelEvent>

GridView::GridView(QWidget *parent) : QGraphicsView(parent)
{
    setRenderHint(QPainter::Antialiasing, true);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
}

void GridView::wheelEvent(QWheelEvent *event)
{
    if (event->angleDelta().ry() > 0){
        scale(1.1, 1.1);
    } else {
        scale(1/1.1, 1/1.1);
    }
}
