#pragma once

#include <QMainWindow>
#include "grid/gridscene.h"
#include "grid/gridview.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
/**
 * @brief The MainWindow class главный экран
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief MainWindow конструктор
     * @param parent родительский объект
     */
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui; //!< графический интерфейс
    GridView *gridView_; //!< отображение сетки
    GridScene *scene_; //!< данные сетки
    /**
     * @brief closeEvent обработка закрытия окна
     * @param event событие
     */
    void closeEvent(QCloseEvent *event);

private slots:
    /**
     * @brief on_pbCreateWalls_clicked создание стен
     */
    void on_pbCreateWalls_clicked();
    /**
     * @brief on_sbWidth_valueChanged кол-во клеток по горизонтали
     * @param arg1 кол-во
     */
    void on_sbWidth_valueChanged(int arg1);
    /**
     * @brief on_sbHeight_valueChanged кол-во клеток клеток по вертикали
     * @param arg1 кол-во
     */
    void on_sbHeight_valueChanged(int arg1);

};
