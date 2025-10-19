#pragma once

#include <QGraphicsRectItem>
/**
 * @brief The WallItem class
 */
class WallItem : public QGraphicsRectItem
{
public:
    /**
     * @brief WallItem конструктор
     * @param parent родительский элемент
     */
    explicit WallItem(QGraphicsItem *parent = Q_NULLPTR);

private:
    /**
     * @brief paint отрисовка элемента
     * @param painter объект рисования
     * @param option параметры
     * @param widget род. элемент
     */
    virtual void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget = Q_NULLPTR) override;
};

