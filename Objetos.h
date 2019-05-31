# ifndef OBJETOS.H
# define OBJETOS_H

#include <QtOpenGL>

#include <iostream>
#include <bits/stdc++.h>

class Objetos
{
public :
    Objetos ();

private :
    void readOBJFile ( const QString & fileName );
    void genNormals ();

    unsigned int numVertices;
    unsigned int numFaces;

    std::vector<QVector4D> vertices;
    std::vector<unsigned int> indices ;
    std::vector<QVector3D> vertNormals;
    std::queue<intDoub> vertVn;
    QVector3D * normals ;

    QVector4D midpoint;
    double invdiag;
};

#endif // OBJETOS_H