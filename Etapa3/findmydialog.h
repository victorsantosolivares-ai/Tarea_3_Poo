#ifndef FINDMYDIALOG_H
#define FINDMYDIALOG_H

#include <QDialog>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QTimer>
#include "ETNube.h"

class FindMyDialog : public QDialog {
    Q_OBJECT
public:
    // duenio: el nombre de la persona cuyo celular fue presionado
    explicit FindMyDialog(const QString& duenio, QWidget* parent = nullptr);

private slots:
    void actualizarTabla();

private:
    QString nombreDuenio;
    QTableWidget* tabla;
    QTimer* timerActualizacion;
};

#endif // FINDMYDIALOG_H
