#include "territoryview.h"
#include <QMessageBox>

TerritoryView::TerritoryView(Territory* terr, QObject* parent)
    : QGraphicsScene(parent), modelo(terr) {

    // Cargar la imagen usando el dato del modelo
    QPixmap background(modelo->getBackgroundImagePath());

    if (!background.isNull()) {
        this->addPixmap(background);
        this->setSceneRect(background.rect());
    }
}

TerritoryView::~TerritoryView() {
    delete modelo;
}

void TerritoryView::addCelularView(CelularView* vista) {
    this->addItem(vista);
}
