#include "Equipo.h"
#include <cmath>
#include <cstdlib>

Equipo::Equipo(QString name, float startX, float startY, float rap, float ang, float dAng)
    : ownerName(name), x(startX), y(startY), rapidez(rap), angulo(ang), deltaAngulo(dAng) {}

float Equipo::getX() const { return x; }
float Equipo::getY() const { return y; }
QString Equipo::getOwnerName() const { return ownerName; }

void Equipo::mover(float deltaT, float anchoMapa, float altoMapa) {
    // 1. Modificar el ángulo aleatoriamente en el rango [-deltaAngulo, +deltaAngulo]
    // Usamos una fórmula sencilla para obtener un float aleatorio
    float variacion = -deltaAngulo + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (2 * deltaAngulo)));
    angulo += variacion;

    // Convertir a radianes para la matemática
    float radianes = angulo * M_PI / 180.0f;

    // 2. Calcular la nueva posición
    float vx = rapidez * cos(radianes);
    float vy = rapidez * sin(radianes); // En Qt, la Y crece hacia abajo

    x += vx * deltaT;
    y += vy * deltaT;

    // 3. Lógica de rebote en los bordes
    if (x < 0) {
        x = 0;
        angulo = 180.0f - angulo; // Rebote pared izquierda
    } else if (x > anchoMapa) {
        x = anchoMapa;
        angulo = 180.0f - angulo; // Rebote pared derecha
    }

    if (y < 0) {
        y = 0;
        angulo = -angulo; // Rebote techo
    } else if (y > altoMapa) {
        y = altoMapa;
        angulo = -angulo; // Rebote suelo
    }
}