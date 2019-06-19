#include "Player.h"
#include <QDebug>

Player::Player()
{
    curvaBezier.append(QVector3D (0.0 , 0.054 , 0.0));
    curvaBezier.append(QVector3D (0.0 , 0.25 , 0.05));
    curvaBezier.append(QVector3D (0.0 , 0.054 , 0.1));

    t = 0.0;
    posInicialPuloX = 0.0;
    posInicialPuloZ = 0.0;
}


void Player::move(bool * keyDirection)
{
    //Coloca o player no chão, se ele estiver pulando
    this->fall();

    qreal result = 0.0, directions=0;

    if(keyDirection[0]){
        result+=180;
        directions++;
    }
    if(keyDirection[1]) {
        result+=270.0;
        directions++;
    }
    if(keyDirection[2]){
        result+=0.0;
        directions++;
    }
    if(keyDirection[3]){
        result+=90.0;
        directions++;
    }
    if(keyDirection[1] && keyDirection[2])//Ultimo quadrante, angulo oposto
       rotY = 315.0;
    else
       rotY = result/directions;

    if(keyDirection[0]) posZ = ( posZ - 0.0025 );
    if(keyDirection[1]) posX = ( posX - 0.0025 );
    if(keyDirection[2]) posZ = ( posZ + 0.0025 );
    if(keyDirection[3]) posX = ( posX + 0.0025 );

    double sinX = sin( posX * 50 );
    double sinZ = sin( posZ * 50 );

    rotY = ( rotY + 20.0 * ( sinX * sinX + sinZ * sinZ ) - 10.0 );

}

void Player::jump()
{
    if( t < 0.025 ){
       t += 0.025;

      posInicialPuloX = posX;
      posInicialPuloZ = posZ;
    }else if( t < 1.0 ){

       t += 0.025;
       QVector3D ptCurva =  bezier( curvaBezier );

       posX = ptCurva.x() + posInicialPuloX;
       posY = ptCurva.y();
       posZ = ptCurva.z() + posInicialPuloZ;

   } else {
        t = 0.0;
   }
}

QVector3D Player::getPlayerPos()
{
    return QVector3D(posX,posY,posZ);
}

QVector3D Player::bezier( QVector<QVector3D> points){
    if (points.size() == 1 ){
        return points[0];
    } else {
        QVector3D p1 = bezier ( points.mid(0,1) );
        QVector3D p2 = bezier ( points.mid(1,-1) );
        QVector3D p = ( 1 - t ) * p1 + t * p2;
        return p;
    }
}

void Player::fall()
{
    this->posY = 0.054;
    this->t = 0.0;
}
