#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QtOpenGL>
#include <fstream>
#include <limits>
#include "Objeto.h"
#include "Player.h"

class GLWidget : public QGLWidget
{
    Q_OBJECT

public :
    explicit GLWidget (QWidget * parent);
    virtual ~GLWidget ();
    void zoomIn();
    void zoomOut();
    void changeCamera(unsigned long i);
    void interact( bool * keyDirection );
    void setShader(int s);

protected :
    void initializeGL ();
    void resizeGL ( int width , int height );
    void paintGL ();
    void mouseMoveEvent ( QMouseEvent * event );
    void mousePressEvent ( QMouseEvent * event );
    void mouseReleaseEvent ( QMouseEvent * event );
    void wheelEvent ( QWheelEvent * event );

public slots :
    void showObj ();
    void timerUpdate();

private:
    Player player;
    Objeto * objetos;
    Objeto * orbitas;
    Objeto * blocos;
    double zoom;
    Camera camera;

    std::vector<Camera> cameras;
    int cameraIdx;
    Light light ;
    Material material;
    GLuint cubeTextures[6];
    TrackBall trackBall ;
    int flagAbertura;

    QMatrix4x4 worldViewMatrix;
    QMatrix4x4 projectionMatrix;

    int flagAparecer[4];
};

#endif // GLWIDGET_H
