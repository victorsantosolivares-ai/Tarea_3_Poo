#ifndef TABLETVIEW_H
#define TABLETVIEW_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QTimer>
#include <QList>
#include "Tablet.h"

class TabletView : public QObject, public QGraphicsRectItem {
    Q_OBJECT
private:
    Tablet* modelo;
    QGraphicsTextItem* textoNombre;

    // Radar
    QTimer* timerBip;
    QTimer* timerRadar;
    QGraphicsEllipseItem* circularRadar;
    float radioActual;
    static constexpr float RADIO_MAX = 50.0f;

    QList<QGraphicsItem*>* listaEquipos;

public:
    explicit TabletView(Tablet* tab, QObject* parent = nullptr);
    ~TabletView();

    Tablet* getModelo();
    void setListaEquipos(QList<QGraphicsItem*>* lista);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private slots:
    void iniciarRadar();
    void animarRadar();
    void mostrarFindMy();
};

#endif // TABLETVIEW_H
