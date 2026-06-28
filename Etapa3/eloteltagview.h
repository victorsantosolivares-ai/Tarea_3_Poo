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

    // Radar
    QTimer* timerBip;       // Dispara cada 4s para iniciar la animación de radar
    QTimer* timerRadar;     // Anima el círculo creciendo (cada ~50ms)
    QGraphicsEllipseItem* circularRadar; // El círculo visual que crece
    float radioActual;
    static constexpr float RADIO_MAX = 50.0f;

    // Lista de celulares en la escena (se setea desde TerritoryView)
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
