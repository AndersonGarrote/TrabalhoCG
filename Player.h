#ifndef PLAYER_H
#define PLAYER_H
#include "Objeto.h"

class Player : public Objeto
{

private:
    QVector<QVector3D> curvaBezier;
    double t;
    double posInicialPuloX, posInicialPuloY, posInicialPuloZ;
    double anguloOrbita;

public:
    Player();

    void move(bool *keyDirection);
    void jump();
    void fall();

    QVector3D getPlayerPos();

    double getanguloOrbita(int ang);

    void anguloOrbitaIncrement(double increment);

private:
    QVector3D bezier(QVector<QVector3D> pointList);

};

#endif // PLAYER_H
