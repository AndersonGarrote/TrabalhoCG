# include "Light.h"

Light :: Light ()
{
    position = QVector4D (2.0 , 2.0 , 2.0 , 0.0) ;
    ambient = QVector4D (1.0 , 1.0 , 1.0 , 1.0) ;
    diffuse = QVector4D (1.0 , 1.0 , 1.0 , 1.0) ;
    specular = QVector4D (1.0 , 1.0 , 1.0 , 1.0) ;
}
