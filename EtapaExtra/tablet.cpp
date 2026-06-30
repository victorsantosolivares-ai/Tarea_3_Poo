#include "tablet.h"

Tablet::Tablet(QString nombre, QString duenio, float startX, float startY,
               float rap, float ang, float dAng)
    : Equipo(nombre, startX, startY, rap, ang, dAng), duenio(duenio) {}
