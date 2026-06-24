#include "Equipo.h"

Equipo::Equipo(QString name, float startX, float startY)
    : ownerName(name), x(startX), y(startY) {}

float Equipo::getX() const { return x; }
float Equipo::getY() const { return y; }
QString Equipo::getOwnerName() const { return ownerName; }

