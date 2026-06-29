#ifndef FINDMYDIALOG_H
#define FINDMYDIALOG_H

#include <QDialog>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QTimer>
#include <QMap>
#include <QGraphicsScene>
#include <QGraphicsPathItem>
#include "ETNube.h"

class FindMyDialog : public QDialog {
    Q_OBJECT
public:
    explicit FindMyDialog(const QString& duenio, QGraphicsScene* escena,
                          QWidget* parent = nullptr);
    ~FindMyDialog();

private slots:
    void actualizarTabla();
    void toggleTraza(const QString& nombreEquipo, QPushButton* btn);

private:
    QString nombreDuenio;
    QTableWidget* tabla;
    QGraphicsScene* escena;
    QTimer* timerActualizacion;

    // nombreEquipo → item de trayectoria activo (nullptr si está oculta)
    QMap<QString, QGraphicsPathItem*> trazas;

    void dibujarTraza(const QString& nombreEquipo);
    void borrarTraza(const QString& nombreEquipo);
    void redibujarTrazasActivas();
};

#endif // FINDMYDIALOG_H