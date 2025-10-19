#include "gridscene.h"
#include "helper.h"
#include "wallitem.h"
#include <QGraphicsSceneEvent>
#include <QMessageBox>
GridScene::GridScene(QObject *parent) : QGraphicsScene(parent),
    a_(Q_NULLPTR), b_(Q_NULLPTR), w_(1), h_(1), pathItem_(Q_NULLPTR)
{
    finder_.setStackSize(1);
    connect(&finder_, &PathFinder::finished,
            this, [=]{
        removePath();
        pathItem_ = new PathItem(QSize(w_, h_), finder_.getPath());
        addItem(pathItem_);
        update();
    });
}

void GridScene::setGridSize(const int wCount, const int hCount)
{
    w_ = wCount;
    h_ = hCount;
    clear();
    walls_.clear();
    items_.clear();
    a_ = Q_NULLPTR;
    b_ = Q_NULLPTR;
    pathItem_ = Q_NULLPTR;
    QPen pen;
    pen.setColor(Qt::darkBlue);
    pen.setWidth(2);
    setSceneRect(QRect(0, 0, wCount*Helper::ITEM_SIZE, hCount*Helper::ITEM_SIZE));

    for (int h = 0; h <=hCount; h++){
        addLine(0, h*Helper::ITEM_SIZE, width(), h*Helper::ITEM_SIZE, pen);
    }

    for (int w = 0; w <=wCount; w++){
        addLine(w*Helper::ITEM_SIZE, 0, w*Helper::ITEM_SIZE, height(), pen);
    }
    finder_.setSize(QSize(wCount, hCount));
}

void GridScene::addWalls_()
{
    for (auto item : items_){
        removeItem(item);
    }
    items_.clear();
    walls_.clear();

    int count = rand() % (h_ * w_);
    QPoint pointA = QPoint(-1, -1);
    if (a_){
        pointA += convertPointToGridPos(a_->pos());
    }
    for (int i = 0; i < count; i ++){
        QPoint point = QPoint(rand() % w_, rand() % h_);
        if (!walls_.contains(point) && pointA != point){
            walls_ << point;
        }
    }

    for (const auto &point : walls_){
        WallItem *wall = new WallItem();
        addItem(wall);
        wall->setPos(point * Helper::ITEM_SIZE);
        items_ << wall;
    }

    for (auto &point : walls_){
        point += QPoint(1, 1);
    }
    finder_.setWalls(walls_);
    update();
}

bool GridScene::isValid(const QPoint &point)
{
    return point.x() > 0 && point.x() <= w_ && point.y() > 0 && point.y() <= h_;
}

void GridScene::removeA()
{
    if (a_){
        removeItem(a_);
        delete a_;
        a_ = Q_NULLPTR;
    }
}

void GridScene::removeB()
{
    if (b_){
        removeItem(b_);
        delete b_;
        b_ = Q_NULLPTR;
    }
}

void GridScene::removePath()
{
    if (pathItem_){
        removeItem(pathItem_);
        delete pathItem_;
        pathItem_ = Q_NULLPTR;
    }
}

QPoint GridScene::convertPointToGridPos(const QPointF &pointf)
{
    QPoint point = pointf.toPoint();
    QPoint leftTopPoint = point - QPoint(point.x() % Helper::ITEM_SIZE, point.y() % Helper::ITEM_SIZE);
    return (leftTopPoint / Helper::ITEM_SIZE + QPoint(1, 1));
}

void GridScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (!a_) return;
    QPoint point = convertPointToGridPos(event->scenePos());
    if (b_ && convertPointToGridPos(b_->pos()) == point) return;

    if (!isValid(point) || walls_.contains(point) || (a_ && convertPointToGridPos(a_->pos()) == point)){
        removeB();
        removePath();
        return;
    }
     if (b_){
         removeB();
         removePath();
     }
     b_ = addText("B", QFont("Arial", Helper::ITEM_SIZE - 20, true));
     b_->setPos((point - QPoint(1, 1)) * Helper::ITEM_SIZE);
    finder_.setPoints(convertPointToGridPos(a_->pos()), point);
    finder_.start();
}

void GridScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton){
        QPoint point = convertPointToGridPos(event->scenePos());
        if (!isValid(point)){
            return;
        }
        if (walls_.contains(point)){
            QMessageBox::warning(0, "Препятствие!!!", "ошибка установки точки А.");
            return;
        }
        removeA();
        if (!a_){
            a_ = addText("A", QFont("Arial", Helper::ITEM_SIZE - 20, true));
            a_->setPos((point - QPoint(1, 1)) * Helper::ITEM_SIZE);
            if (b_ && convertPointToGridPos(b_->pos()) == point){
                removeB();
            }
        }
    }
}

