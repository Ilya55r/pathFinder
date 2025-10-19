#pragma once

#include <QThread>
#include <QPoint>
#include <QSize>
/**
 * @brief The PathFinder class искатель пути
 */
class PathFinder : public QThread
{
    Q_OBJECT
public:
    /**
     * @brief PathFinder конструктор
     * @param parent родительский объект
     */
    PathFinder(QObject *parent = Q_NULLPTR);
    /**
     * @brief setSize установка размера сетки
     * @param size размер
     */
    void setSize(const QSize &size);
    /**
     * @brief setWalls установка ограждений
     * @param list список точек
     */
    void setWalls(const QList<QPoint> &list);
    /**
     * @brief setPoints установка начальной и конечной точки
     * @param pointA начальная точка
     * @param pointB конечная точка
     */
    void setPoints(const QPoint &pointA, const QPoint &pointB);
    /**
     * @brief getPath получение пути
     * @return путь
     */
    QList<QPoint> getPath() const;

private:
    QSize size_; //!< размер
    QList<QPoint> walls_; //!< ограждения
    QPair<QPoint, QPoint> points_;//!< точки
    QList<QPoint> path_; //!< путь
    /**
     * @brief bfs поиск путь в ширину
     */
    void bfs();
    /**
     * @brief dfs поиск пути в глубину
     */
    void dfs();
    /**
     * @brief isValid проверка условий выхода за границу
     * @param point точка
     * @return валидность
     */
    bool isValid(const QPoint &point);
    /**
     * @brief run работа потока
     */
    void run() override;
    /**
     * @brief pointToString преобразование точки к строке
     * @param p точка
     * @return строка
     */
    QString pointToString(const QPoint &p);

};
