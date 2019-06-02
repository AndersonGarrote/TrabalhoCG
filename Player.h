#ifndef PLAYER_H
#define PLAYER_H
#include "Objeto.h"

class Player : public Objeto
{
public:
    Player();
public:

    void move(bool *keyDirection);

    QVector3D getPlayerPos();

};

#endif // PLAYER_H
