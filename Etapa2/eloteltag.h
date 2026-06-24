#ifndef ELOTELTAG_H
#define ELOTELTAG_H
#include "Equipo.h"

class EloTelTag : public Equipo {
public:
    EloTelTag(QString name, float startX, float startY, float rap, float ang, float dAng);
};

#endif // ELOTELTAG_H
