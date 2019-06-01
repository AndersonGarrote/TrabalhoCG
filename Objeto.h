# ifndef OBJETO_H
# define OBJETO_H

#include <QtOpenGL>

#include <iostream>
#include <bits/stdc++.h>
#include "Camera.h"
#include "Light.h"
#include "Material.h"
#include "TrackBall.h"

typedef std::pair<int, double> intDoub;
class Objeto
{
public :
    Objeto ();
    ~Objeto ();
    void paintGL ();
    void readOBJFile ( const QString & fileName );
    void genNormals ();
    void createVBOs ();
    void destroyVBOs ();
    void createShaders ();
    void destroyShaders ();
    void resizeGL ( int width , int height );
    void setModelViewMatrix( QMatrix4x4 matrix);
    void setMaterial(Material mat);
    void setLight(Light li);
    void setPosition(double x, double y, double z);
    void setScale(double x, double y, double z);

private :
    unsigned int numVertices;
    unsigned int numFaces;
    unsigned int currentShader ;
    std::vector<QVector4D> vertices;
    std::vector<unsigned int> indices ;
    std::vector<QVector3D> vertNormals;
    std::queue<intDoub> vertVn;
    QVector3D * normals ;

    QVector4D midpoint;
    double posX, posY, posZ;

    double invdiag;

    QMatrix4x4 modelViewMatrix ;
    QMatrix4x4 projectionMatrix ;

    QGLBuffer * vboVertices ;
    QGLBuffer * vboNormals ;
    QGLBuffer * vboIndices;

    QGLShaderProgram * shaderProgram ;
    QGLShader * vertexShader ;
    QGLShader * fragmentShader ;
    Light light ;
    Material material ;
    //TrackBall trackBall ;
};

#endif // OBJETO_H
