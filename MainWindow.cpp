#include "MainWindow.h"
#include "ui_mainwindow.h"

#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    for (int i=0; i<4; i++)
        keyDirection[i] = false;

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

void MainWindow::keyPressEvent(QKeyEvent * event)
{
    switch ( event->key() )
    {
    case Qt::Key_W:
    case Qt::Key_Up:
        keyDirection[0] = true;
        break;
    case Qt::Key_A:
    case Qt::Key_Left:
        keyDirection[1] = true;
        break;
    case Qt::Key_S:
    case Qt::Key_Down:
        keyDirection[2] = true;
        break;
    case Qt::Key_D:
    case Qt::Key_Right:
        keyDirection[3] = true;
        break;
    default:
        return;
    break;
    }
    ui->glwidget->interact(keyDirection);
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if(!event->isAutoRepeat()){
        switch ( event->key() )
        {
        case Qt::Key_W:
        case Qt::Key_Up:
            keyDirection[0] = false;
            break;
        case Qt::Key_A:
        case Qt::Key_Left:
            keyDirection[1] = false;
            break;
        case Qt::Key_S:
        case Qt::Key_Down:
            keyDirection[2] = false;
            break;
        case Qt::Key_D:
        case Qt::Key_Right:
            keyDirection[3] = false;
            break;
        }
    }
}
