#include "Material.h"

Material :: Material ()
{
    ambient = QVector4D (0.3,  0.3, 0.3, 1.0) ;
    diffuse = QVector4D (0.7 , 0.7 , 0.7 , 1.0) ;
    specular = QVector4D (0.6 , 0.6 , 0.6 , 1.0) ;
    shininess = 100.0;
}
