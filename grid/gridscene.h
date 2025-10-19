#pragma once

#include <QGraphicsScene>
#include <QMouseEvent>
#include "pathitem.h"
#include <pathFinder/pathfinder.h>
/**
 * @brief The GridScene class
 */
class GridScene : public QGraphicsScene
{
    Q_OBJECT
public:
    /**
     * @brief GridScene конструктор
     * @param parent родительский объект
     */
    GridScene(QObject *parent = Q_NULLPTR);
    /**
     * @brief setGridSize установка размера сетки
     * @param wCount кол-во клеток по горизонтали
     * @param hCount кол-во клеток по вертикали
     */
    void setGridSize(const int wCount, const int hCount);
    /**
     * @brief addWalls_ добавление стен
     */
    void addWalls_();

private:
    QList<QGraphicsItem*> items_; //!< стены
    QGraphicsItem *a_, *b_; //!< точки
    quint16 w_, h_; //!< размер
    QList<QPoint> walls_; //!< точки стен
    PathItem *pathItem_; //!< путь
    PathFinder finder_; //!< поисковик
    /**
     * @brief isValid проверка на выход за границы
     * @param point точка
     * @return валидность
     */
    bool isValid(const QPoint &point);
    /**
     * @brief removeA удаление точки "А"
     */
    void removeA();
    /**
     * @brief removeB удаление точки "В"
     */
    void removeB();
    /**
     * @brief removePath удаление пути
     */
    void removePath();
    /**
     * @brief convertPointToGridPos преобразование координат
     * @param pointf точка
     * @return новая точка
     */
    QPoint convertPointToGridPos(const QPointF &pointf);
    /**
     * @brief mouseMoveEvent обработка движения мыши
     * @param event событие
     */
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    /**
     * @brief mousePressEvent обработка нажатия мыши
     * @param event событие
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

