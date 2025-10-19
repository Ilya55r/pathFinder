#pragma once
#include <QGraphicsItem>
#include <QPoint>
/**
 * @brief The PathItem class путь
 */
class PathItem : public QGraphicsItem
{    
public:
    /**
     * @brief PathItem конструктор
     * @param size размер элемента
     * @param points точки пути
     */
    explicit PathItem(const QSize &size, const QList<QPoint> &points);

private:
    /**
     * @brief boundingRect границы элемента
     * @return положение и границы элемента
     */
    QRectF boundingRect() const override;
    /**
     * @brief paint отрисовка элемента
     * @param painter элемент рисования
     * @param option параметры
     * @param widget
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) override;

private:
    QList<QPoint> points_; //!< точки пути
    QSize size_; //!< размер элемента
};


