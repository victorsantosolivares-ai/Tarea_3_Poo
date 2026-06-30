#ifndef TERRITORYVIEW_H
#define TERRITORYVIEW_H

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QList>
#include "Territory.h"

class TerritoryView : public QGraphicsScene {
    Q_OBJECT
private:
    Territory* modelo;
    float deltaTiempo;
    QList<QGraphicsItem*> equiposVisuales;

public:
    TerritoryView(Territory* terr, QObject* parent = nullptr);
    ~TerritoryView();

    void setDeltaTiempo(float dt);
    void addEquipoVisual(QGraphicsItem* vista);

    // Devuelve puntero a la lista interna para que tags/tablets puedan buscar celulares
    QList<QGraphicsItem*>* getListaEquipos() { return &equiposVisuales; }

public slots:
    void updateSimulation();
};

#endif // TERRITORYVIEW_H
