#ifndef TABLET_H
#define TABLET_H
#include "Equipo.h"

class Tablet : public Equipo {
public:
    Tablet(QString name, float startX, float startY, float rap, float ang, float dAng);
};

#endif // TABLET_H
