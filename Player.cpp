#include "Player.h"

Player::Player()
{

}


void Player::move(bool * keyDirection)
{
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

    if(keyDirection[0]) posZ = ( posZ - 0.005 );
    if(keyDirection[1]) posX = ( posX - 0.005 );
    if(keyDirection[2]) posZ = ( posZ + 0.005 );
    if(keyDirection[3]) posX = ( posX + 0.005 );

    double sinX = sin( posX * 50 );
    double sinZ = sin( posZ * 50 );

    rotY = ( rotY + 20.0 * ( sinX * sinX + sinZ * sinZ ) - 10.0 );

}

QVector3D Player::getPlayerPos()
{
    return QVector3D(posX,posY,posZ);
}
