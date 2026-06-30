#include "findmydialog.h"
#include <QHeaderView>
#include <QPainterPath>
#include <QPen>
#include <QDebug>

FindMyDialog::FindMyDialog(const QString& duenio, QGraphicsScene* escena, QWidget* parent)
    : QDialog(parent), nombreDuenio(duenio), escena(escena)
{
    setWindowTitle("Find My – " + duenio);
    resize(500, 300);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Equipos de: <b>" + duenio + "</b>", this));

    tabla = new QTableWidget(0, 4, this);
    tabla->setHorizontalHeaderLabels({"Equipo", "X (px)", "Y (px)", "Traza"});
    tabla->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    tabla->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    tabla->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    tabla->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    tabla->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tabla->setAlternatingRowColors(true);
    layout->addWidget(tabla);

    // Actualización cada 1 segundo mientras la ventana esté abierta
    timerActualizacion = new QTimer(this);
    timerActualizacion->setInterval(1000);
    connect(timerActualizacion, &QTimer::timeout, this, &FindMyDialog::actualizarTabla);
    timerActualizacion->start();

    actualizarTabla(); // carga inicial inmediata
}

FindMyDialog::~FindMyDialog() {
    // Borrar todas las trazas activas del mapa al cerrar
    for (auto it = trazas.begin(); it != trazas.end(); ++it) {
        if (it.value() && escena) {
            escena->removeItem(it.value());
            delete it.value();
        }
    }
}

void FindMyDialog::actualizarTabla() {
    const QList<ReporteEquipo>& todos = ETNube::instancia().todos();

    // Recopilar equipos de esta persona
    QList<const ReporteEquipo*> miEquipos;
    for (const ReporteEquipo& r : todos)
        if (r.duenioEquipo == nombreDuenio)
            miEquipos.append(&r);

    // Ajustar filas si aparecen equipos nuevos
    tabla->setRowCount(miEquipos.size());

    for (int i = 0; i < miEquipos.size(); ++i) {
        const ReporteEquipo* r = miEquipos[i];
        const QString& equipo = r->nombreEquipo;

        // Actualizar celdas de posición
        tabla->setItem(i, 0, new QTableWidgetItem(equipo));
        tabla->setItem(i, 1, new QTableWidgetItem(QString::number(r->x, 'f', 1)));
        tabla->setItem(i, 2, new QTableWidgetItem(QString::number(r->y, 'f', 1)));

        // Crear botón solo si la fila es nueva (no tiene widget aún)
        if (!tabla->cellWidget(i, 3)) {
            trazas[equipo] = nullptr;

            QPushButton* btnTraza = new QPushButton("Mostrar traza", this);
            connect(btnTraza, &QPushButton::clicked, this, [this, equipo, btnTraza]() {
                toggleTraza(equipo, btnTraza);
            });
            tabla->setCellWidget(i, 3, btnTraza);
        }

        // Redibujar trazas activas con el historial actualizado
        if (trazas.value(equipo) != nullptr) {
            borrarTraza(equipo);
            dibujarTraza(equipo);
        }
    }
}

void FindMyDialog::toggleTraza(const QString& nombreEquipo, QPushButton* btn) {
    if (trazas.value(nombreEquipo) != nullptr) {
        borrarTraza(nombreEquipo);
        btn->setText("Mostrar traza");
    } else {
        dibujarTraza(nombreEquipo);
        btn->setText(trazas.value(nombreEquipo) != nullptr ? "Ocultar traza" : "Mostrar traza");
    }
}

void FindMyDialog::dibujarTraza(const QString& nombreEquipo) {
    if (!escena) return;

    const QList<ReporteEquipo>& todos = ETNube::instancia().todos();
    const QList<QPointF>* puntos = nullptr;
    for (const ReporteEquipo& r : todos) {
        if (r.nombreEquipo == nombreEquipo) {
            puntos = &r.historial;
            break;
        }
    }

    if (!puntos || puntos->isEmpty()) return;

    QPainterPath path;
    path.moveTo(puntos->first());
    if (puntos->size() == 1) {
        path.addEllipse(puntos->first(), 5, 5);
    } else {
        for (int i = 1; i < puntos->size(); ++i)
            path.lineTo((*puntos)[i]);
    }

    QGraphicsPathItem* item = escena->addPath(path, QPen(Qt::magenta, 2));
    item->setZValue(100);
    trazas[nombreEquipo] = item;
}

void FindMyDialog::borrarTraza(const QString& nombreEquipo) {
    QGraphicsPathItem* item = trazas.value(nombreEquipo);
    if (item && escena) {
        escena->removeItem(item);
        delete item;
    }
    trazas[nombreEquipo] = nullptr;
}