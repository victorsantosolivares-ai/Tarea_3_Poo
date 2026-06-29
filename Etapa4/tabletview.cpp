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

    // tbip de tablets puede ser diferente — usamos 5 segundos
    timerBip = new QTimer(this);
    timerBip->setInterval(5000);
    connect(timerBip, &QTimer::timeout, this, &TabletView::iniciarRadar);
    QTimer::singleShot(rand() % 5000, this, [this]() { timerBip->start(); });

    timerRadar = new QTimer(this);
    timerRadar->setInterval(50);
    connect(timerRadar, &QTimer::timeout, this, &TabletView::animarRadar);
}

TabletView::~TabletView() { delete modelo; }

Tablet* TabletView::getModelo() { return modelo; }

void TabletView::setListaEquipos(QList<QGraphicsItem*>* lista) {
    listaEquipos = lista;
}

void TabletView::iniciarRadar() {
    if (timerRadar->isActive()) return;
    radioActual = 0.0f;
    if (circularRadar) { delete circularRadar; circularRadar = nullptr; }

    circularRadar = new QGraphicsEllipseItem(this);
    circularRadar->setPen(QPen(Qt::darkGreen, 1));
    circularRadar->setBrush(Qt::NoBrush);
    circularRadar->setRect(12.5f - radioActual, 17.5f - radioActual, radioActual * 2, radioActual * 2);
    timerRadar->start();
}

void TabletView::animarRadar() {
    radioActual += RADIO_MAX / 20.0f;

    if (circularRadar)
        circularRadar->setRect(12.5f - radioActual, 17.5f - radioActual, radioActual * 2, radioActual * 2);

    if (radioActual >= RADIO_MAX) {
        timerRadar->stop();

        // Detectar celulares dentro del radio
        if (listaEquipos) {
            float tx = modelo->getX() + 12.5f;
            float ty = modelo->getY() + 17.5f;

            for (QGraphicsItem* item : *listaEquipos) {
                CelularView* celular = dynamic_cast<CelularView*>(item);
                if (!celular) continue;

                float cx = celular->getModelo()->getX() + 7.5f;
                float cy = celular->getModelo()->getY() + 15.0f;
                float dist = std::sqrt((cx-tx)*(cx-tx) + (cy-ty)*(cy-ty));

                if (dist <= RADIO_MAX) {
                    // El celular reporta: nombre tablet, dueño tablet, posición del CELULAR
                    ETNube::instancia().reportar(
                        modelo->getOwnerName(),
                        modelo->getDuenio(),
                        celular->getModelo()->getOwnerName(),
                        celular->getModelo()->getX(),
                        celular->getModelo()->getY()
                    );
                }
            }
        }

        if (circularRadar) { delete circularRadar; circularRadar = nullptr; }
    }
}

void TabletView::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    if (event->button() == Qt::RightButton || event->button() == Qt::LeftButton) {
        QMenu menu;
        QAction* accionFindMy = menu.addAction("Find My");
        QAction* seleccion = menu.exec(event->screenPos().toPointF().toPoint());
        if (seleccion == accionFindMy)
            mostrarFindMy();
    }
    QGraphicsRectItem::mousePressEvent(event);
}

void TabletView::mostrarFindMy() {
    FindMyDialog* dialogo = new FindMyDialog(modelo->getDuenio(), this->scene());
    dialogo->setAttribute(Qt::WA_DeleteOnClose);
    dialogo->show();
}
