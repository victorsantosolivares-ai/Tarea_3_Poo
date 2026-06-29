#ifndef ELOTELTAG_H
#define ELOTELTAG_H
#include "Equipo.h"

class EloTelTag : public Equipo {
private:
    QString duenio; // persona dueña del tag (ej: "Diego")
public:
    EloTelTag(QString nombre, QString duenio, float startX, float startY,
              float rap, float ang, float dAng);
    QString getDuenio() const { return duenio; }
};

#endif // ELOTELTAG_H
