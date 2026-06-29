#ifndef CELULARVIEW_H
#define CELULARVIEW_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QTimer>
#include "Celular.h"

class CelularView : public QObject, public QGraphicsRectItem {
    Q_OBJECT
private:
    Celular* modelo;
    QGraphicsTextItem* textoNombre;
    QTimer* timerBip;
    QTimer* timerRadar;
    QGraphicsEllipseItem* circularRadar;
    float radioActual;

public:
    explicit CelularView(Celular* cel, QObject* parent = nullptr);
    ~CelularView();
    Celular* getModelo();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private slots:
    void iniciarRadar();
    void animarRadar();
    void mostrarFindMy();
};

#endif // CELULARVIEW_H
