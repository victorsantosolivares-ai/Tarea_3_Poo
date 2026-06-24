#include "tabletview.h"
#include <QBrush>
#include <QFont>

TabletView::TabletView(Tablet* tab) : modelo(tab) {
    // La tablet es un poco más grande que el celular (ej: 25x35) y de color verde
    setRect(0, 0, 25, 35);
    setBrush(Qt::green);
    setPos(modelo->getX(), modelo->getY());

    textoNombre = new QGraphicsTextItem(modelo->getOwnerName(), this);
    textoNombre->setDefaultTextColor(Qt::black);
    QFont font = textoNombre->font();
    font.setBold(true);
    textoNombre->setFont(font);
    textoNombre->setPos(28, 0);
}

TabletView::~TabletView() {
    delete modelo;
}

Tablet* TabletView::getModelo() {
    return modelo;
}