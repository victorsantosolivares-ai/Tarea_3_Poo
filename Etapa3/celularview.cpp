#include "CelularView.h"
#include "ETNube.h"
#include "FindMyDialog.h"
#include <QBrush>
#include <QFont>
#include <QMenu>
#include <QGraphicsSceneMouseEvent>

CelularView::CelularView(Celular* cel, QObject* parent)
    : QObject(parent), QGraphicsRectItem(nullptr), modelo(cel)
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

    // Timer reservado para etapas futuras
    timerReporte = new QTimer(this);
    timerReporte->setInterval(4000);
    connect(timerReporte, &QTimer::timeout, this, &CelularView::reportarPosicion);
    timerReporte->start();
}

CelularView::~CelularView() {
    delete modelo;
}

Celular* CelularView::getModelo() {
    return modelo;
}

void CelularView::reportarPosicion() {
    // Los reportes los generan los tags/tablets cuando detectan este celular.
    // Este timer queda disponible para etapas futuras.
}

void CelularView::mousePressEvent(QGraphicsSceneMouseEvent* event) {
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

void CelularView::mostrarFindMy() {
    FindMyDialog* dialogo = new FindMyDialog(modelo->getOwnerName());
    dialogo->setAttribute(Qt::WA_DeleteOnClose);
    dialogo->show();
}