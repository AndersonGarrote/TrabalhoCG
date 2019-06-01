#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QtOpenGL>

#include <iostream>
#include <bits/stdc++.h>
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
    void interact( bool * keyDirection );

protected :
    void initializeGL ();
    void resizeGL ( int width , int height );
    void paintGL ();

    void mouseMoveEvent ( QMouseEvent * event );
    void mousePressEvent ( QMouseEvent * event );
    void mouseReleaseEvent ( QMouseEvent * event );
    void wheelEvent ( QWheelEvent * event );

    void timerEvent(QTimerEvent *event) override;
public slots :

    void showObj ();

private:
    void readOBJFile ( const QString & fileName );

    void createVBOs ();
    void genNormals ();
    void updateBuffers();

    unsigned int currentShader ;

    unsigned int numVertices ;
    unsigned int numFaces ;

    std::vector<QVector4D> vertices;
    std::queue<intDoub> vertVn;
    std::vector<QVector3D> vertNormals;
    QVector4D midpoint;
    double invdiag;
    QVector3D * normals ;
    std::vector<unsigned int> indices ;

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
    int _numFaces;
    int _numVertices;

    //Atributos de Interação
    QVector3D playerRot;
    QVector3D playerPos;
    int callBackTimer;
    bool nextMove;

    QGLShaderProgram * shaderProgram ;
    QGLShader * vertexShader ;
    QGLShader * fragmentShader ;

    void createShaders ();

    void destroyShaders ();

    void destroyVBOs ();

    void updateView();

};

#endif // GLWIDGET_H
