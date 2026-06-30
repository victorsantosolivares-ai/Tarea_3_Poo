#ifndef ELOTELTAGVIEW_H
#define ELOTELTAGVIEW_H

#include <QObject>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QTimer>
#include <QList>
#include "EloTelTag.h"

class EloTelTagView : public QObject, public QGraphicsEllipseItem {
    Q_OBJECT
private:
    EloTelTag* modelo;
    QGraphicsTextItem* textoNombre;
    QTimer* timerBip;
    QTimer* timerRadar;
    QGraphicsEllipseItem* circularRadar;
    float radioActual;
    static constexpr float RADIO_MAX = 50.0f;
    QList<QGraphicsItem*>* listaEquipos;

public:
    explicit EloTelTagView(EloTelTag* tag, QObject* parent = nullptr);
    ~EloTelTagView();
    EloTelTag* getModelo();
    void setListaEquipos(QList<QGraphicsItem*>* lista);

private slots:
    void iniciarRadar();
    void animarRadar();
};

#endif // ELOTELTAGVIEW_H
