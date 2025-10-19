#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QSettings>
#include "helper.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Поиск пути");
    gridView_ = new GridView(this);
    ui->vlGraphView->addWidget(gridView_);
    scene_ = new GridScene(gridView_);
    gridView_->setScene(scene_);

    QSettings settings(Helper::Setting::COMPANY, Helper::Setting::PROGRAM_NAME);
    QSize size = settings.value(Helper::Setting::SIZE).toSize();
    QRect rect = settings.value(Helper::Setting::GEOMETRY).toRect();
    ui->sbWidth->blockSignals(true);
    ui->sbWidth->setValue(size.width());
    ui->sbWidth->blockSignals(false);
    ui->sbHeight->setValue(size.height());
    resize(QSize(rect.width(), rect.height()));
    move(rect.x(), rect.y());
}

MainWindow::~MainWindow()
{
    delete ui;

    if (gridView_){
        delete gridView_;
    }

    if (scene_){
        delete scene_;
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QSettings settings(Helper::Setting::COMPANY, Helper::Setting::PROGRAM_NAME);
    settings.setValue(Helper::Setting::GEOMETRY, geometry());
    settings.setValue(Helper::Setting::SIZE, QSize(ui->sbWidth->value(), ui->sbHeight->value()));
    settings.sync();
    QMainWindow::closeEvent(event);
}

void MainWindow::on_pbCreateWalls_clicked()
{
    if (scene_){
        scene_->addWalls_();
    }
}

void MainWindow::on_sbWidth_valueChanged(int arg1)
{
    if (scene_){
        scene_->setGridSize(arg1, ui->sbHeight->value());
    }
}

void MainWindow::on_sbHeight_valueChanged(int arg1)
{
    if (scene_){
        scene_->setGridSize(ui->sbWidth->value(), arg1);
    }
}

