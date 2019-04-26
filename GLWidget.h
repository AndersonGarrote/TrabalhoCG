#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QtOpenGL>

#include <iostream>
#include <fstream>
#include <limits>

#include "Camera.h"
#include "Light.h"
#include "Material.h"
#include "TrackBall.h"

class GLWidget : public QGLWidget
{
    Q_OBJECT
public :
    explicit GLWidget (QWidget * parent);
    virtual ~GLWidget ();

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

    void showFileOpenDialog ();

private:
    void readVTKFile ( const QString & fileName );

    void createVBOs ();
    void genNormals ();
    void updateBuffers();

    unsigned int currentShader ;

    unsigned int numVertices ;
    unsigned int numFaces ;

    QVector4D * vertices ;
    QVector3D * normals ;
    unsigned int * indices ;

    QMatrix4x4 modelViewMatrix ;
    QMatrix4x4 projectionMatrix ;
    Camera camera ;
    Light light ;
    Material material ;
    TrackBall trackBall ;
    double zoom ;

    QGLBuffer * vboVertices ;
    QGLBuffer * vboNormals ;
    QGLBuffer * vboIndices;
    int _numFaces;
    int _numVertices;

    QGLShaderProgram * shaderProgram ;
    QGLShader * vertexShader ;
    QGLShader * fragmentShader ;


    void createShaders ();
    void destroyShaders ();


    void destroyVBOs ();

    void updateView();
};

#endif // GLWIDGET_H
