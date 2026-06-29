#include "territoryview.h"
#include "CelularView.h"
#include "EloTelTagView.h"
#include "TabletView.h"

TerritoryView::TerritoryView(Territory* terr, QObject* parent)
    : QGraphicsScene(parent), modelo(terr)
{
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
    equiposVisuales.append(vista);
}

void TerritoryView::updateSimulation() {
    float ancho = this->width();
    float alto  = this->height();

    for (QGraphicsItem* item : equiposVisuales) {

        CelularView* vistaCelular = dynamic_cast<CelularView*>(item);
        if (vistaCelular) {
            vistaCelular->getModelo()->mover(deltaTiempo, ancho, alto);
            vistaCelular->setPos(vistaCelular->getModelo()->getX(), vistaCelular->getModelo()->getY());
            continue;
        }

        EloTelTagView* vistaTag = dynamic_cast<EloTelTagView*>(item);
        if (vistaTag) {
            vistaTag->getModelo()->mover(deltaTiempo, ancho, alto);
            vistaTag->setPos(vistaTag->getModelo()->getX(), vistaTag->getModelo()->getY());
            continue;
        }

        TabletView* vistaTablet = dynamic_cast<TabletView*>(item);
        if (vistaTablet) {
            vistaTablet->getModelo()->mover(deltaTiempo, ancho, alto);
            vistaTablet->setPos(vistaTablet->getModelo()->getX(), vistaTablet->getModelo()->getY());
        }
    }
}
