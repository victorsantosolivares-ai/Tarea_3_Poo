#ifndef TABLET_H
#define TABLET_H
#include "Equipo.h"

class Tablet : public Equipo {
private:
    QString duenio;
public:
    Tablet(QString nombre, QString duenio, float startX, float startY,
           float rap, float ang, float dAng);
    QString getDuenio() const { return duenio; }
};

#endif // TABLET_H
