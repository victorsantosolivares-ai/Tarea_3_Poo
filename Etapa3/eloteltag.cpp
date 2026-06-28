#include "eloteltag.h"

EloTelTag::EloTelTag(QString nombre, QString duenio, float startX, float startY,
                     float rap, float ang, float dAng)
    : Equipo(nombre, startX, startY, rap, ang, dAng), duenio(duenio) {}
