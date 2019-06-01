#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QtOpenGL>
#include <fstream>
#include <limits>
/*
#include "Camera.h"
#include "Light.h"
#include "Material.h"
#include "TrackBall.h"*/
#include "Objeto.h"


class GLWidget : public QGLWidget
{
    Q_OBJECT
public :
    explicit GLWidget (QWidget * parent);
    virtual ~GLWidget ();

    void zoomIn();
    void zoomOut();
    void changeCamera(unsigned long i);

    
protected :
    void initializeGL ();
    void resizeGL ( int width , int height );
    void paintGL ();

    void mouseMoveEvent ( QMouseEvent * event );
    void mousePressEvent ( QMouseEvent * event );
    void mouseReleaseEvent ( QMouseEvent * event );
    void wheelEvent ( QWheelEvent * event );
    void keyPressEvent ( QKeyEvent * event );


public slots :

    void showObj ();

private:
    

    
    //void updateBuffers();

    
    Objeto *objetos; 
    double zoom;
    Camera camera;
    
    std::vector<Camera> cameras;
    Light light ;
    Material material ;
    TrackBall trackBall ;

	int flagAbertura;

    //void updateView();
};

#endif // GLWIDGET_H
