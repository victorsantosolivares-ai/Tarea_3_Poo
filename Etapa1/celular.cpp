#include "Celular.h"

Celular::Celular(QString name, float startX, float startY, float rap, float ang, float dAng)
    : Equipo(name, startX, startY), rapidez(rap), angulo(ang), deltaAngulo(dAng) {}

