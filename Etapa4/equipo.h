#ifndef EQUIPO_H
#define EQUIPO_H
#include <QString>

class Equipo
{
protected:
    QString ownerName;
    float x;
    float y;
    float rapidez;
    float angulo; // En grados
    float deltaAngulo;
public:
    Equipo(QString name, float startX, float startY, float rap, float ang, float dAng);
    virtual ~Equipo() {} // Destructor virtual

    float getX() const;
    float getY() const;
    QString getOwnerName() const;

    // NUEVA FUNCIÓN: La matemática del movimiento
    void mover(float deltaT, float anchoMapa, float altoMapa);
};

#endif // EQUIPO_H
