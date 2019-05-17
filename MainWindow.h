#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtOpenGL>

#include "Camera.h"
#include "Light.h"
#include "Material.h"
#include "TrackBall.h"

#include "GLWidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:
    void on_actionSair_triggered();

    void on_actionZoom_in_triggered();

    void on_actionZoom_out_triggered();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
