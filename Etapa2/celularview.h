#ifndef CELULARVIEW_H
#define CELULARVIEW_H
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include "Celular.h"

// Hereda de QGraphicsRectItem para poder dibujarse como un rectángulo
class CelularView : public QGraphicsRectItem {
private:
    Celular* modelo; // Puntero a la lógica pura
    QGraphicsTextItem* textoNombre; // Etiqueta flotante
public:
    CelularView(Celular* cel);
    ~CelularView();

    Celular* getModelo();
};

#endif // CELULARVIEW_H
