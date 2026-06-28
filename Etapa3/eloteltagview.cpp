#include "EloTelTagView.h"
#include "CelularView.h"
#include "ETNube.h"
#include <QBrush>
#include <QPen>
#include <QFont>
#include <QGraphicsScene>
#include <cstdlib>  // rand()

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

    // Timer de bip: cada 4 segundos, con offset aleatorio inicial para no sincronizarse
    timerBip = new QTimer(this);
    timerBip->setInterval(4000);
    connect(timerBip, &QTimer::timeout, this, &EloTelTagView::iniciarRadar);

    // Offset aleatorio entre 0 y 4000ms para desincronizar los tags
    int offsetInicial = rand() % 4000;
    QTimer::singleShot(offsetInicial, this, [this]() { timerBip->start(); });

    // Timer de animación radar: ~20 pasos en 1 segundo => cada 50ms
    timerRadar = new QTimer(this);
    timerRadar->setInterval(50);
    connect(timerRadar, &QTimer::timeout, this, &EloTelTagView::animarRadar);
}

EloTelTagView::~EloTelTagView() {
    delete modelo;
}

EloTelTag* EloTelTagView::getModelo() {
    return modelo;
}

void EloTelTagView::setListaEquipos(QList<QGraphicsItem*>* lista) {
    listaEquipos = lista;
}

void EloTelTagView::iniciarRadar() {
    // Si ya hay una animación en curso, no iniciar otra
    if (timerRadar->isActive()) return;

    radioActual = 0.0f;

    // Crear el círculo de radar en la escena (centrado en el tag)
    if (circularRadar) {
        if (scene()) scene()->removeItem(circularRadar);
        delete circularRadar;
    }
    circularRadar = new QGraphicsEllipseItem(this);
    circularRadar->setPen(QPen(Qt::red, 1));
    circularRadar->setBrush(Qt::NoBrush);
    // Centrado relativo al item (que tiene rect 0,0,12,12 → centro en 6,6)
    circularRadar->setRect(-radioActual + 6, -radioActual + 6, radioActual * 2, radioActual * 2);

    timerRadar->start();
}

void EloTelTagView::animarRadar() {
    radioActual += RADIO_MAX / 20.0f; // 20 pasos para llegar a 50px en 1 segundo

    if (circularRadar) {
        circularRadar->setRect(-radioActual + 6, -radioActual + 6, radioActual * 2, radioActual * 2);
    }

    if (radioActual >= RADIO_MAX) {
        timerRadar->stop();

        // Verificar si algún celular fue alcanzado
        if (listaEquipos) {
            float tagX = modelo->getX();
            float tagY = modelo->getY();

            for (QGraphicsItem* item : *listaEquipos) {
                CelularView* celular = dynamic_cast<CelularView*>(item);
                if (!celular) continue;

                float dx = celular->getModelo()->getX() - tagX;
                float dy = celular->getModelo()->getY() - tagY;
                float distancia = std::sqrt(dx * dx + dy * dy);

                if (distancia <= RADIO_MAX) {
                    ETNube::instancia().reportar(
                        modelo->getOwnerName(),          // nombre del tag (ej: "maleta")
                        modelo->getDuenio(),             // dueño del tag (ej: "Pedro")
                        celular->getModelo()->getOwnerName(), // dueño del celular que lo detectó
                        celular->getModelo()->getX(),
                        celular->getModelo()->getY()
                    );
                }
            }
        }

        // Eliminar el círculo
        if (circularRadar) {
            if (scene()) scene()->removeItem(circularRadar);
            delete circularRadar;
            circularRadar = nullptr;
        }
    }
}
