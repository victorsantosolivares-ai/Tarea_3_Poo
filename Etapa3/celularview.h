#ifndef CELULARVIEW_H
#define CELULARVIEW_H

#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QObject>
#include <QTimer>
#include "Celular.h"

// Hereda de QObject (para signals/slots) Y de QGraphicsRectItem (para dibujarse)
class CelularView : public QObject, public QGraphicsRectItem {
    Q_OBJECT
private:
    Celular* modelo;
    QGraphicsTextItem* textoNombre;
    QTimer* timerReporte; // Cada 4 segundos reporta posición a ETNube

public:
    explicit CelularView(Celular* cel, QObject* parent = nullptr);
    ~CelularView();

    Celular* getModelo();

protected:
    // Para detectar clic derecho y mostrar menú contextual
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private slots:
    void reportarPosicion();
    void mostrarFindMy();
};

#endif // CELULARVIEW_H
