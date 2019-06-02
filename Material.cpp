#include "Material.h"

Material :: Material ()
{
    ambient = QVector4D (0.3,  0.3, 0.3, 1.0) ;
    diffuse = QVector4D (0.7 , 0.7 , 0.7 , 1.0) ;
    specular = QVector4D (0.6 , 0.6 , 0.6 , 1.0) ;
    shininess = 100.0;
}

Material Material::setMaterial(QString materialName)
{
    if(materialName == "green_plastic"){
        ambient = QVector4D (1/255.0, 136/255.0, 60/255.0 , 1.0) ;
        diffuse = QVector4D (35/255.0, 106/255.0, 56/255.0, 1.0);
        specular = QVector4D (109.0/255.0, 162.0/255.0, 113.0/255.0, 1.0) ;
        shininess = 25.0;
    }else if (materialName == "yellow_plastic") {
        ambient = QVector4D (246/255.0, 217/255.0, 3/255.0 , 1.0) ;
        diffuse = QVector4D (186/255.0, 123/255.0, 32/255.0, 1.0);
        specular = QVector4D (254/255.0, 236/255.0, 152/255.0, 1.0);
        shininess = 25.0;
    }else{
        ambient = QVector4D (0.3,  0.3, 0.3, 1.0) ;
        diffuse = QVector4D (0.7 , 0.7 , 0.7 , 1.0) ;
        specular = QVector4D (0.6 , 0.6 , 0.6 , 1.0) ;
        shininess = 100.0;
    }
    return *this;
}


