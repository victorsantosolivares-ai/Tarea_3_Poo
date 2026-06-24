#ifndef TERRITORYVIEW_H
#define TERRITORYVIEW_H
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include "Territory.h"
#include "CelularView.h"

class TerritoryView : public QGraphicsScene {
private:
    Territory* modelo;
public:
    TerritoryView(Territory* terr, QObject* parent = nullptr);
    ~TerritoryView();

    void addCelularView(CelularView* vista);
};
#endif // TERRITORYVIEW_H
