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

void MainWindow::on_actionWiki_triggered()
{
    QDesktopServices::openUrl(QUrl("https://github.com/AndersonGarrote/TrabalhoCG/wiki"));
}

void MainWindow::on_actionCamera_1_triggered()
{
    ui->glwidget->changeCamera(0);
}

void MainWindow::on_actionCamera_2_triggered()
{
    ui->glwidget->changeCamera(1);
}


