#include "CelularView.h"
#include <QBrush>
#include <QFont>

CelularView::CelularView(Celular* cel) : modelo(cel) {
    // 1. Configurar la forma del celular (ej: 15px de ancho por 30px de alto)
    setRect(0, 0, 15, 30);
    setBrush(Qt::blue); // Los celulares serán azules

    // 2. Ubicar la vista en la misma posición que dicta el modelo
    setPos(modelo->getX(), modelo->getY());

    // 3. Crear el texto flotante para el nombre del dueño
    textoNombre = new QGraphicsTextItem(modelo->getOwnerName(), this);
    textoNombre->setDefaultTextColor(Qt::black);
    QFont font = textoNombre->font();
    font.setBold(true);
    textoNombre->setFont(font);

    // Posicionar el texto un poco a la derecha del celular
    textoNombre->setPos(18, 0);
}

CelularView::~CelularView() {
    // Qt se encarga de limpiar el textoNombre por ser "hijo" (this),
    // pero debemos limpiar el modelo si es responsabilidad nuestra
    delete modelo;
}

Celular* CelularView::getModelo() {
    return modelo;
}