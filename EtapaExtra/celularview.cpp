#include "CelularView.h"
#include "FindMyDialog.h"
#include "GFindMyDialog.h"
#include <QBrush>
#include <QPen>
#include <QFont>
#include <QMenu>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <cstdlib>

CelularView::CelularView(Celular* cel, QObject* parent)
    : QObject(parent), QGraphicsRectItem(nullptr), modelo(cel),
      circularRadar(nullptr), radioActual(0.0f)
{
    setRect(0, 0, 15, 30);
    setBrush(Qt::blue);
    setPos(modelo->getX(), modelo->getY());
    setAcceptedMouseButtons(Qt::LeftButton | Qt::RightButton);

    textoNombre = new QGraphicsTextItem(modelo->getOwnerName(), this);
    textoNombre->setDefaultTextColor(Qt::black);
    QFont font = textoNombre->font();
    font.setBold(true);
    textoNombre->setFont(font);
    textoNombre->setPos(18, 0);

    // Radar visual cada 4 segundos — solo animación, sin detección
    timerBip = new QTimer(this);
    timerBip->setInterval(4000);
    connect(timerBip, &QTimer::timeout, this, &CelularView::iniciarRadar);
    int offset = rand() % 4000;
    QTimer::singleShot(offset, this, [this]() { timerBip->start(); });

    timerRadar = new QTimer(this);
    timerRadar->setInterval(50);
    connect(timerRadar, &QTimer::timeout, this, &CelularView::animarRadar);
}

CelularView::~CelularView() {
    delete modelo;
}

Celular* CelularView::getModelo() { return modelo; }

void CelularView::iniciarRadar() {
    if (timerRadar->isActive()) return;
    radioActual = 0.0f;
    if (circularRadar) { delete circularRadar; circularRadar = nullptr; }

    circularRadar = new QGraphicsEllipseItem(this);
    circularRadar->setPen(QPen(Qt::blue, 1));
    circularRadar->setBrush(Qt::NoBrush);
    circularRadar->setRect(7.5f - radioActual, 15.0f - radioActual,
                           radioActual * 2, radioActual * 2);
    timerRadar->start();
}

void CelularView::animarRadar() {
    radioActual += 50.0f / 20.0f; // 50px en 1 segundo (20 pasos x 50ms)

    if (circularRadar)
        circularRadar->setRect(7.5f - radioActual, 15.0f - radioActual,
                               radioActual * 2, radioActual * 2);

    if (radioActual >= 50.0f) {
        timerRadar->stop();
        if (circularRadar) { delete circularRadar; circularRadar = nullptr; }
        // Sin detección aquí — la hacen los tags/tablets
    }
}

void CelularView::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    if (event->button() == Qt::RightButton || event->button() == Qt::LeftButton) {
        QMenu menu;
        QAction* accionFindMy = menu.addAction("Find My");
        QAction* accionGFindMy = menu.addAction("GFindMy");
        QAction* seleccion = menu.exec(event->screenPos().toPointF().toPoint());
        if (seleccion == accionFindMy)
            mostrarFindMy();
        else if (seleccion == accionGFindMy)
            mostrarGFindMy();
    }
    QGraphicsRectItem::mousePressEvent(event);
}

void CelularView::mostrarFindMy() {
    FindMyDialog* dialogo = new FindMyDialog(modelo->getOwnerName(), this->scene());
    dialogo->setAttribute(Qt::WA_DeleteOnClose);
    dialogo->show();
}

void CelularView::mostrarGFindMy() {
    GFindMyDialog* dialogo = new GFindMyDialog(modelo->getOwnerName(), imagenFondo, nullptr);
    dialogo->setAttribute(Qt::WA_DeleteOnClose);
    dialogo->show();
}
