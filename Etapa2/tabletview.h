#ifndef TABLETVIEW_H
#define TABLETVIEW_H
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include "Tablet.h"

class TabletView : public QGraphicsRectItem {
private:
    Tablet* modelo;
    QGraphicsTextItem* textoNombre;
public:
    TabletView(Tablet* tab);
    ~TabletView();
    Tablet* getModelo(); // IMPORTANTE para poder moverlo
};

#endif // TABLETVIEW_H
