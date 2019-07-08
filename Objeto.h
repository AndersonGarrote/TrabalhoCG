# ifndef OBJETO_H
# define OBJETO_H

#include <QtOpenGL>
#include <QPixmap>

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
    void paintGL (QMatrix4x4 projectionMatrix);
    void readOBJFile ( const QString & fileName );
    void genNormals ();
    void genTextures ();
    void createVBOs ();
    void destroyVBOs ();
    void createShaders ();
    void destroyShaders ();
    void setModelViewMatrix( QMatrix4x4 matrix);
    void setMaterial(Material mat);
    void setLight(Light li);
    void setPosition(double x, double y, double z);
    void setRotation(double angle, double x, double y, double z);
    void setTranslation(double x, double y, double z);
    void setScale(double x, double y, double z);
    void genMagicCube();
    void genMagicCubeNormals();
    void paintCubeGL(QMatrix4x4 projectionMatrix, GLuint * textures);
    void createTextureShaders();
    QVector3D getObjetoPos();

protected:
    double posX, posY, posZ;
    double rotX, rotY, rotZ;
    double scaX, scaY, scaZ;
private :
    unsigned int numVertices;
    unsigned int numFaces;
    unsigned int currentShader ;
    std::vector<QVector4D> vertices;
    std::vector<QVector2D> vertTexture;
    std::vector<unsigned int> indices ;
    std::vector<QVector3D> vertNormals;
    std::queue<intDoub> vertVn;
    std::queue<intDoub> vertVt;
    QVector3D * normals ;

    QVector4D midpoint;
    double invdiag;

    QMatrix4x4 modelViewMatrix ;
    QGLBuffer * vboVertices ;
    QGLBuffer * vboNormals ;
    QGLBuffer * vboIndices;
    QGLBuffer * vboTextureCoords;
    QGLShaderProgram * shaderProgram ;
    QGLShader * vertexShader ;
    QGLShader * fragmentShader ;
    QGLBuffer * vboTexCoords ;
    Light light ;
    Material material ;

    QVector<QVector2D> texCoords;

};

#endif // OBJETO_H
