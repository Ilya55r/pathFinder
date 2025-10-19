#pragma once
#include "global.h"
#include <QGraphicsView>
/**
 * @brief The GridView class отображение сетки
 */
GRIDSHAREDLIB_EXPORT class GridView : public QGraphicsView
{
    Q_OBJECT
public:
    /**
     * @brief GridView конструктор
     * @param parent родительский объект
     */
    explicit GridView(QWidget *parent = Q_NULLPTR);

private:
    /**
     * @brief wheelEvent обработка колесика мыши
     * @param event событие
     */
    void wheelEvent(QWheelEvent *event) override;
};

