#include "eloteltagview.h"
#include <QBrush>
#include <QFont>

EloTelTagView::EloTelTagView(EloTelTag* tag) : modelo(tag) {
    // El Tag se dibuja como un círculo pequeño rojo (ej: 12x12)
    setRect(0, 0, 12, 12);
    setBrush(Qt::red);
    setPos(modelo->getX(), modelo->getY());

    textoNombre = new QGraphicsTextItem(modelo->getOwnerName(), this);
    textoNombre->setDefaultTextColor(Qt::black);
    QFont font = textoNombre->font();
    font.setBold(true);
    textoNombre->setFont(font);
    textoNombre->setPos(15, -5);
}

EloTelTagView::~EloTelTagView() {
    delete modelo;
}

EloTelTag* EloTelTagView::getModelo() {
    return modelo;
}