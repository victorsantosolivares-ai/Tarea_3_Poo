#include "territoryview.h"
#include <QMessageBox>
#include "CelularView.h"
#include "EloTelTagView.h"
#include "TabletView.h"

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

void TerritoryView::setDeltaTiempo(float dt) {
    deltaTiempo = dt;
}

void TerritoryView::addEquipoVisual(QGraphicsItem* vista) {
    this->addItem(vista);
    equiposVisuales.append(vista); // Guardarlo en nuestra lista
}

void TerritoryView::updateSimulation() {
    // Dimensiones del mapa para los rebotes
    float ancho = this->width();
    float alto = this->height();

    // Recorremos todos los elementos guardados
    for (QGraphicsItem* item : equiposVisuales) {

        // 1. Intentar mover como Celular
        CelularView* vistaCelular = dynamic_cast<CelularView*>(item);
        if (vistaCelular) {
            vistaCelular->getModelo()->mover(deltaTiempo, ancho, alto);
            vistaCelular->setPos(vistaCelular->getModelo()->getX(), vistaCelular->getModelo()->getY());
            continue; // Si logramos moverlo, saltamos a la siguiente iteración del for
        }

        // 2. Intentar mover como EloTelTag
        EloTelTagView* vistaTag = dynamic_cast<EloTelTagView*>(item);
        if (vistaTag) {
            vistaTag->getModelo()->mover(deltaTiempo, ancho, alto);
            vistaTag->setPos(vistaTag->getModelo()->getX(), vistaTag->getModelo()->getY());
            continue;
        }

        // 3. Intentar mover como Tablet
        TabletView* vistaTablet = dynamic_cast<TabletView*>(item);
        if (vistaTablet) {
            vistaTablet->getModelo()->mover(deltaTiempo, ancho, alto);
            vistaTablet->setPos(vistaTablet->getModelo()->getX(), vistaTablet->getModelo()->getY());
        }
    }
}