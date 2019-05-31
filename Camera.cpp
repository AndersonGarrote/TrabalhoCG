#include "Camera.h"

Camera :: Camera ()
{
    eye = QVector3D (0.0 , 0.0 , 1.0) ;
    at = QVector3D (0.0 , 0.0 , 0.0) ;
    up = QVector3D (0.0 , 1.0 , 0.0) ;
}

void Camera :: setCamera(QVector3D eye, QVector3D at, QVector3D up) {
    this->eye.setX(0.0); this->eye.setY(0.0); this->eye.setZ(0.0);
    this->eye += eye;

    this->at.setX(0.0); this->at.setY(0.0); this->at.setZ(0.0);
    this->at += at;

    this->up.setX(0.0); this->up.setY(0.0); this->up.setZ(0.0);
    this->up += up;
}
