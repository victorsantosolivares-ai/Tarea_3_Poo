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

    void setDeltaTiempo(float dt); // Setter para guardar el tiempo
    void addEquipoVisual(QGraphicsItem* vista);

public slots: // Esta sección es especial de Qt
    void updateSimulation();
};
#endif // TERRITORYVIEW_H
