# ifndef CAMERA_H
# define CAMERA_H

# include <QVector3D>

class Camera
{
public :
    Camera ();

    void setCamera(QVector3D eye, QVector3D at, QVector3D up);
    void zoom(double zoom);

    QVector3D eye;
    QVector3D at;
    QVector3D up;
    QVector3D posRelativa;
};


#endif // CAMERA_H
