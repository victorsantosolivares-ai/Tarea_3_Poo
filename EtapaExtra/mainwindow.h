#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QAction>
#include "TerritoryView.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow* ui;
    TerritoryView*  miTerritorioVisual;
    QTimer*         relojSimulacion;
    float           deltaTiempo;

    // Menú Simulation
    QAction* accionPlay;
    QAction* accionPause;

    void loadConfiguration(const QString& filePath);
    void setupMenu();

private slots:
    void onPlay();
    void onPause();
};

#endif // MAINWINDOW_H
