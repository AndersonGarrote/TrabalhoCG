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

    void on_actionWiki_triggered();

    void on_actionCamera_1_triggered();

    void on_actionCamera_2_triggered();

    void keyPressEvent(QKeyEvent * event);

    void keyReleaseEvent(QKeyEvent * event);

private:
    Ui::MainWindow *ui;

    bool keyDirection[5];
};

#endif // MAINWINDOW_H
