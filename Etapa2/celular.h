#ifndef CELULAR_H
#define CELULAR_H
#include "Equipo.h"

class Celular : public Equipo {
public:
    Celular(QString name, float startX, float startY, float rap, float ang, float dAng);
};

#endif // CELULAR_H
