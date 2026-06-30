#ifndef GFINDMYDIALOG_H
#define GFINDMYDIALOG_H

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QGraphicsTextItem>
#include <QTimer>
#include <QMap>
#include <QString>
#include "ETNube.h"

// Ventana "Graphics Find My": réplica visual del mapa con solo los equipos de una persona
class GFindMyDialog : public QDialog {
    Q_OBJECT
public:
    // duenio: persona dueña de los equipos a mostrar
    // imagenFondo: mismo path usado por TerritoryView
    explicit GFindMyDialog(const QString& duenio, const QString& imagenFondo,
                           QWidget* parent = nullptr);

private slots:
    void actualizarVistas();

private:
    QString nombreDuenio;
    QGraphicsScene* escenaPropia;
    QGraphicsView* vista;
    QTimer* timerActualizacion;

    // nombreEquipo → marcador en la escena propia
    QMap<QString, QGraphicsEllipseItem*> marcadores;
    QMap<QString, QGraphicsTextItem*> etiquetas;

    void crearOActualizarMarcador(const QString& nombreEquipo, float x, float y);
};

#endif // GFINDMYDIALOG_H
