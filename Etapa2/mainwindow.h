#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "TerritoryView.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
    TerritoryView *miTerritorioVisual; //Añade el territorio
    QTimer *relojSimulacion; //Timer
    float deltaTiempo; //Tiempo del .txt
    void loadConfiguration(const QString &filePath); //Lee .txt
};
#endif // MAINWINDOW_H
