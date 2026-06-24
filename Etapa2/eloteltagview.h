#ifndef ELOTELTAGVIEW_H
#define ELOTELTAGVIEW_H
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include "EloTelTag.h"

class EloTelTagView : public QGraphicsEllipseItem {
private:
    EloTelTag* modelo;
    QGraphicsTextItem* textoNombre;
public:
    EloTelTagView(EloTelTag* tag);
    ~EloTelTagView();
    EloTelTag* getModelo();
};

#endif // ELOTELTAGVIEW_H
