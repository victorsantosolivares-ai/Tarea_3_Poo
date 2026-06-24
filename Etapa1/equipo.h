#ifndef EQUIPO_H
#define EQUIPO_H
#include <QString>

class Equipo
{
protected:
    QString ownerName;
    float x;
    float y;
public:
    Equipo(QString name, float startX, float startY);
    virtual ~Equipo() {} // Destructor virtual

    float getX() const;
    float getY() const;
    QString getOwnerName() const;
};

#endif // EQUIPO_H
