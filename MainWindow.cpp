#include "MainWindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
     ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionSair_triggered()
{
    this->close();
}

void MainWindow::on_actionZoom_in_triggered()
{
    ui->glwidget->zoomIn();
}

void MainWindow::on_actionZoom_out_triggered()
{
    ui->glwidget->zoomOut();
}
