#ifndef CELULAR_H
#define CELULAR_H
#include "Equipo.h"

class Celular : public Equipo {
private:
    float rapidez;
    float angulo;
    float deltaAngulo;
public:
    Celular(QString name, float startX, float startY, float rap, float ang, float dAng);
};

#endif // CELULAR_H
