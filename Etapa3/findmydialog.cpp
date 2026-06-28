#include "findmydialog.h"
#include <QHeaderView>

FindMyDialog::FindMyDialog(const QString& duenio, QWidget* parent)
    : QDialog(parent), nombreDuenio(duenio)
{
    setWindowTitle("Find My – " + duenio);
    resize(450, 300);

    QVBoxLayout* layout = new QVBoxLayout(this);

    QLabel* titulo = new QLabel("Equipos de: <b>" + duenio + "</b>", this);
    layout->addWidget(titulo);

    tabla = new QTableWidget(0, 4, this);
    tabla->setHorizontalHeaderLabels({"Equipo", "Últ. X (px)", "Últ. Y (px)", "Hora detección"});
    tabla->horizontalHeader()->setStretchLastSection(true);
    tabla->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tabla->setAlternatingRowColors(true);
    layout->addWidget(tabla);

    QLabel* nota = new QLabel("<i>Solo aparecen equipos detectados por un celular.</i>", this);
    layout->addWidget(nota);

    // Actualiza cada 1 segundo mientras la ventana esté abierta
    timerActualizacion = new QTimer(this);
    connect(timerActualizacion, &QTimer::timeout, this, &FindMyDialog::actualizarTabla);
    timerActualizacion->start(1000);

    actualizarTabla(); // mostrar datos iniciales
}

void FindMyDialog::actualizarTabla()
{
    // Busca equipos cuyo dueño sea esta persona
    QList<ReporteEquipo> reportes = ETNube::instancia().obtenerEquiposDe(nombreDuenio);

    tabla->setRowCount(reportes.size());

    for (int i = 0; i < reportes.size(); ++i) {
        const ReporteEquipo& r = reportes[i];
        tabla->setItem(i, 0, new QTableWidgetItem(r.nombreEquipo));
        tabla->setItem(i, 1, new QTableWidgetItem(QString::number(r.x, 'f', 1)));
        tabla->setItem(i, 2, new QTableWidgetItem(QString::number(r.y, 'f', 1)));
        tabla->setItem(i, 3, new QTableWidgetItem(r.timestamp.toString("hh:mm:ss")));
    }
}
