#ifndef GLWIDGET_H
#define GLWIDGET_H


#include <fstream>
#include <limits>

#include "Camera.h"
#include "Light.h"
#include "Material.h"
#include "TrackBall.h"

typedef std::pair<int, double> intDoub;

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
    

    void createVBOs ();
    void updateBuffers();

    unsigned int currentShader ;





    QMatrix4x4 modelViewMatrix ;
    QMatrix4x4 projectionMatrix ;
    Camera camera;
    std::vector<Camera> cameras;
    Light light ;
    Material material ;
    TrackBall trackBall ;
    double zoom ;
	int flagAbertura;
    QGLBuffer * vboVertices ;
    QGLBuffer * vboNormals ;
    QGLBuffer * vboIndices;


    QGLShaderProgram * shaderProgram ;
    QGLShader * vertexShader ;
    QGLShader * fragmentShader ;


    void createShaders ();
    void destroyShaders ();


    void destroyVBOs ();

    void updateView();
};

#endif // GLWIDGET_H
