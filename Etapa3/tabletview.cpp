#include "TabletView.h"
#include "CelularView.h"
#include "ETNube.h"
#include "FindMyDialog.h"
#include <QBrush>
#include <QPen>
#include <QFont>
#include <QMenu>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsEllipseItem>
#include <cmath>
#include <cstdlib>

TabletView::TabletView(Tablet* tab, QObject* parent)
    : QObject(parent), QGraphicsRectItem(nullptr), modelo(tab),
      circularRadar(nullptr), radioActual(0.0f), listaEquipos(nullptr)
{
    setRect(0, 0, 25, 35);
    setBrush(Qt::green);
    setPos(modelo->getX(), modelo->getY());

    setAcceptedMouseButtons(Qt::LeftButton | Qt::RightButton);

    textoNombre = new QGraphicsTextItem(modelo->getOwnerName(), this);
    textoNombre->setDefaultTextColor(Qt::black);
    QFont font = textoNombre->font();
    font.setBold(true);
    textoNombre->setFont(font);
    textoNombre->setPos(28, 0);

    // Bip cada 5 segundos (tablets usan 5s según el enunciado)
    timerBip = new QTimer(this);
    timerBip->setInterval(5000);
    connect(timerBip, &QTimer::timeout, this, &TabletView::iniciarRadar);

    int offsetInicial = rand() % 5000;
    QTimer::singleShot(offsetInicial, this, [this]() { timerBip->start(); });

    timerRadar = new QTimer(this);
    timerRadar->setInterval(50);
    connect(timerRadar, &QTimer::timeout, this, &TabletView::animarRadar);
}

TabletView::~TabletView() {
    delete modelo;
}

Tablet* TabletView::getModelo() {
    return modelo;
}

void TabletView::setListaEquipos(QList<QGraphicsItem*>* lista) {
    listaEquipos = lista;
}

void TabletView::iniciarRadar() {
    if (timerRadar->isActive()) return;

    radioActual = 0.0f;

    if (circularRadar) {
        if (scene()) scene()->removeItem(circularRadar);
        delete circularRadar;
    }
    circularRadar = new QGraphicsEllipseItem(this);
    circularRadar->setPen(QPen(Qt::darkGreen, 1));
    circularRadar->setBrush(Qt::NoBrush);
    // Centro relativo al rect 0,0,25,35 → centro en 12.5, 17.5
    circularRadar->setRect(-radioActual + 12.5f, -radioActual + 17.5f, radioActual * 2, radioActual * 2);

    timerRadar->start();
}

void TabletView::animarRadar() {
    radioActual += RADIO_MAX / 20.0f;

    if (circularRadar) {
        circularRadar->setRect(-radioActual + 12.5f, -radioActual + 17.5f, radioActual * 2, radioActual * 2);
    }

    if (radioActual >= RADIO_MAX) {
        timerRadar->stop();

        if (listaEquipos) {
            float tabX = modelo->getX();
            float tabY = modelo->getY();

            for (QGraphicsItem* item : *listaEquipos) {
                CelularView* celular = dynamic_cast<CelularView*>(item);
                if (!celular) continue;

                float dx = celular->getModelo()->getX() - tabX;
                float dy = celular->getModelo()->getY() - tabY;
                float distancia = std::sqrt(dx * dx + dy * dy);

                if (distancia <= RADIO_MAX) {
                    ETNube::instancia().reportar(
                        modelo->getOwnerName(),              // nombre tablet (ej: "Tablet de Pedro")
                        modelo->getDuenio(),                 // dueño tablet (ej: "Pedro")
                        celular->getModelo()->getOwnerName(), // dueño celular detectado
                        celular->getModelo()->getX(),
                        celular->getModelo()->getY()
                    );
                }
            }
        }

        if (circularRadar) {
            if (scene()) scene()->removeItem(circularRadar);
            delete circularRadar;
            circularRadar = nullptr;
        }
    }
}

void TabletView::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    if (event->button() == Qt::RightButton || event->button() == Qt::LeftButton) {
        QMenu menu;
        QAction* accionFindMy = menu.addAction("Find My");
        QAction* seleccion = menu.exec(event->screenPos().toPointF().toPoint());
        if (seleccion == accionFindMy) {
            mostrarFindMy();
        }
    }
    QGraphicsRectItem::mousePressEvent(event);
}

void TabletView::mostrarFindMy() {
    FindMyDialog* dialogo = new FindMyDialog(modelo->getOwnerName());
    dialogo->setAttribute(Qt::WA_DeleteOnClose);
    dialogo->show();
}
