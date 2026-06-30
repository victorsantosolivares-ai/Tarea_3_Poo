#include "gfindmydialog.h"
#include <QVBoxLayout>
#include <QPixmap>
#include <QBrush>
#include <QFont>
#include <QPen>

GFindMyDialog::GFindMyDialog(const QString& duenio, const QString& imagenFondo, QWidget* parent)
    : QDialog(parent), nombreDuenio(duenio)
{
    setWindowTitle("GFindMy – " + duenio);
    resize(700, 500);

    QVBoxLayout* layout = new QVBoxLayout(this);

    escenaPropia = new QGraphicsScene(this);

    // Cargar la misma imagen de fondo que usa la simulación principal
    QPixmap fondo(imagenFondo);
    if (!fondo.isNull()) {
        escenaPropia->addPixmap(fondo);
        escenaPropia->setSceneRect(fondo.rect());
    }

    vista = new QGraphicsView(escenaPropia, this);
    layout->addWidget(vista);

    // Actualización cada 1 segundo según lo que indique ETNube
    timerActualizacion = new QTimer(this);
    timerActualizacion->setInterval(1000);
    connect(timerActualizacion, &QTimer::timeout, this, &GFindMyDialog::actualizarVistas);
    timerActualizacion->start();

    actualizarVistas(); // carga inicial
}

void GFindMyDialog::actualizarVistas() {
    const QList<ReporteEquipo>& todos = ETNube::instancia().todos();

    for (const ReporteEquipo& r : todos) {
        if (r.duenioEquipo == nombreDuenio) {
            crearOActualizarMarcador(r.nombreEquipo, r.x, r.y);
        }
    }
}

void GFindMyDialog::crearOActualizarMarcador(const QString& nombreEquipo, float x, float y) {
    if (marcadores.contains(nombreEquipo)) {
        // Ya existe: solo mover a la nueva posición
        marcadores[nombreEquipo]->setPos(x, y);
        etiquetas[nombreEquipo]->setPos(x + 12, y - 5);
        return;
    }

    // Crear marcador nuevo: círculo naranjo con nombre
    QGraphicsEllipseItem* marcador = escenaPropia->addEllipse(
        0, 0, 14, 14, QPen(Qt::black), QBrush(QColor(255, 140, 0))
    );
    marcador->setPos(x, y);
    marcador->setZValue(10);

    QGraphicsTextItem* etiqueta = escenaPropia->addText(nombreEquipo);
    QFont f = etiqueta->font();
    f.setBold(true);
    etiqueta->setFont(f);
    etiqueta->setDefaultTextColor(Qt::black);
    etiqueta->setPos(x + 12, y - 5);
    etiqueta->setZValue(10);

    marcadores[nombreEquipo] = marcador;
    etiquetas[nombreEquipo] = etiqueta;
}
