#include "EloTelTagView.h"
#include "CelularView.h"
#include "ETNube.h"
#include <QBrush>
#include <QPen>
#include <QFont>
#include <QGraphicsScene>
#include <cmath>
#include <cstdlib>

EloTelTagView::EloTelTagView(EloTelTag* tag, QObject* parent)
    : QObject(parent), QGraphicsEllipseItem(nullptr), modelo(tag),
      circularRadar(nullptr), radioActual(0.0f), listaEquipos(nullptr)
{
    setRect(0, 0, 12, 12);
    setBrush(Qt::red);
    setPos(modelo->getX(), modelo->getY());

    textoNombre = new QGraphicsTextItem(modelo->getOwnerName(), this);
    textoNombre->setDefaultTextColor(Qt::black);
    QFont font = textoNombre->font();
    font.setBold(true);
    textoNombre->setFont(font);
    textoNombre->setPos(15, -5);

    timerBip = new QTimer(this);
    timerBip->setInterval(4000);
    connect(timerBip, &QTimer::timeout, this, &EloTelTagView::iniciarRadar);
    // Offset aleatorio para no sincronizarse
    QTimer::singleShot(rand() % 4000, this, [this]() { timerBip->start(); });

    timerRadar = new QTimer(this);
    timerRadar->setInterval(50);
    connect(timerRadar, &QTimer::timeout, this, &EloTelTagView::animarRadar);
}

EloTelTagView::~EloTelTagView() { delete modelo; }

EloTelTag* EloTelTagView::getModelo() { return modelo; }

void EloTelTagView::setListaEquipos(QList<QGraphicsItem*>* lista) {
    listaEquipos = lista;
}

void EloTelTagView::iniciarRadar() {
    if (timerRadar->isActive()) return;
    radioActual = 0.0f;
    if (circularRadar) { delete circularRadar; circularRadar = nullptr; }

    circularRadar = new QGraphicsEllipseItem(this);
    circularRadar->setPen(QPen(Qt::red, 1));
    circularRadar->setBrush(Qt::NoBrush);
    circularRadar->setRect(6 - radioActual, 6 - radioActual, radioActual * 2, radioActual * 2);
    timerRadar->start();
}

void EloTelTagView::animarRadar() {
    radioActual += RADIO_MAX / 20.0f;

    if (circularRadar)
        circularRadar->setRect(6 - radioActual, 6 - radioActual, radioActual * 2, radioActual * 2);

    if (radioActual >= RADIO_MAX) {
        timerRadar->stop();

        // Detectar celulares dentro del radio
        if (listaEquipos) {
            float tx = modelo->getX() + 6.0f;
            float ty = modelo->getY() + 6.0f;

            for (QGraphicsItem* item : *listaEquipos) {
                CelularView* celular = dynamic_cast<CelularView*>(item);
                if (!celular) continue;

                float cx = celular->getModelo()->getX() + 7.5f;
                float cy = celular->getModelo()->getY() + 15.0f;
                float dist = std::sqrt((cx-tx)*(cx-tx) + (cy-ty)*(cy-ty));

                if (dist <= RADIO_MAX) {
                    // El celular reporta: nombre del tag, dueño del tag, posición del CELULAR
                    ETNube::instancia().reportar(
                        modelo->getOwnerName(),       // ej: "Pedromaleta"
                        modelo->getDuenio(),          // ej: "Pedro"
                        celular->getModelo()->getOwnerName(), // dueño celular
                        celular->getModelo()->getX(), // posición del celular
                        celular->getModelo()->getY()
                    );
                }
            }
        }

        if (circularRadar) { delete circularRadar; circularRadar = nullptr; }
    }
}
