#include "pathfinder.h"
#include <QQueue>
#include <QStack>
#include <QMap>
PathFinder::PathFinder(QObject *parent) : QThread(parent), size_(QSize(1, 1))
{

}

void PathFinder::setSize(const QSize &size)
{
    size_ = size;
}

void PathFinder::setWalls(const QList<QPoint> &list)
{
    walls_ = list;
}

void PathFinder::setPoints(const QPoint &pointA, const QPoint &pointB)
{
    points_ = QPair<QPoint, QPoint>(pointA, pointB);
}

QList<QPoint> PathFinder::getPath() const
{
    return path_;
}

void PathFinder::bfs()
{
     path_.clear();
     QQueue<QPoint> queue;
     QList<QPoint> visited;
     queue.enqueue(points_.first);
     visited << points_.first;
     QMap<QString, QPoint> history;

     QList<QPoint> direction = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

     while(!queue.isEmpty()){
         QPoint point = queue.dequeue();
         if (point == points_.second && !history.isEmpty()){
             path_ << point;
             while (path_.last() != points_.first){
                 QPoint parentPoint = history.take(pointToString(path_.last()));
                 path_ << parentPoint;
             }
             return;
         }

         for (const auto &dir : direction){
             QPoint nextPoint = point + dir;
             if (!walls_.contains(nextPoint) && !visited.contains(nextPoint) && isValid(nextPoint)){
                 visited << nextPoint;
                 history.insert(pointToString(nextPoint), point);
                 queue.enqueue(nextPoint);
             }
         }
     }
}

void PathFinder::dfs()
{
     path_.clear();
     QStack<QPoint> queue;
     QList<QPoint> visited;
     queue.push(points_.first);
     visited << points_.first;
     QMap<QString, QPoint> history;

     QList<QPoint> direction = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
     while(!queue.isEmpty()){
         QPoint point = queue.pop();
         if (point == points_.second && !history.isEmpty()){
             path_ << point;
             while (path_.last() != points_.first){
                 QPoint parentPoint = history.take(pointToString(path_.last()));
                 path_ << parentPoint;
             }
             return;
         }

         for (const auto &dir : direction){
             QPoint nextPoint = point + dir;
             if (!walls_.contains(nextPoint) && !visited.contains(nextPoint) && isValid(nextPoint)){
                 visited << nextPoint;
                 history.insert(pointToString(nextPoint), point);
                 queue.push(nextPoint);
             }
         }
     }
}

bool PathFinder::isValid(const QPoint &point)
{
    return point.x() > 0 && point.x() <= size_.width() && point.y() > 0 && point.y() <= size_.height();
}

void PathFinder::run()
{
    bfs();
}

QString PathFinder::pointToString(const QPoint &p)
{
    return QString("%0;%1").arg(p.x()).arg(p.y());
}
