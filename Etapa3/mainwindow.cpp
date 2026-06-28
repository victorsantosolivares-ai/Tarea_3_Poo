#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QFileInfo>
#include <QMenuBar>

#include "Celular.h"
#include "CelularView.h"
#include "EloTelTag.h"
#include "EloTelTagView.h"
#include "Tablet.h"
#include "TabletView.h"
#include "Territory.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , miTerritorioVisual(nullptr)
    , relojSimulacion(new QTimer(this))
{
    ui->setupUi(this);
    setupMenu();

    QString fileName = QFileDialog::getOpenFileName(this,
        "Seleccionar archivo de configuración", "", "Text Files (*.txt);;All Files (*)");

    if (!fileName.isEmpty()) {
        loadConfiguration(fileName);

        miTerritorioVisual->setDeltaTiempo(deltaTiempo);
        connect(relojSimulacion, &QTimer::timeout, miTerritorioVisual, &TerritoryView::updateSimulation);
        // NO arranca automáticamente: el usuario presiona Play
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setupMenu() {
    QMenu* menuSimulation = menuBar()->addMenu("Simulation");

    accionPlay  = menuSimulation->addAction("Play");
    accionPause = menuSimulation->addAction("Pause");

    accionPause->setEnabled(false); // Al inicio no hay nada corriendo

    connect(accionPlay,  &QAction::triggered, this, &MainWindow::onPlay);
    connect(accionPause, &QAction::triggered, this, &MainWindow::onPause);
}

void MainWindow::onPlay() {
    if (miTerritorioVisual && !relojSimulacion->isActive()) {
        relojSimulacion->start(static_cast<int>(deltaTiempo * 1000));
        accionPlay->setEnabled(false);
        accionPause->setEnabled(true);
    }
}

void MainWindow::onPause() {
    if (relojSimulacion->isActive()) {
        relojSimulacion->stop();
        accionPlay->setEnabled(true);
        accionPause->setEnabled(false);
    }
}

void MainWindow::loadConfiguration(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    QTextStream in(&file);

    QString backgroundFileName = in.readLine().trimmed();
    QFileInfo fileInfo(filePath);
    QString imagePath = fileInfo.absolutePath() + "/" + backgroundFileName;

    Territory* territorioModelo = new Territory(imagePath);
    miTerritorioVisual = new TerritoryView(territorioModelo, this);
    ui->graphicsView->setScene(miTerritorioVisual);

    in >> deltaTiempo;

    int numeroPersonas;
    in >> numeroPersonas;

    for (int i = 0; i < numeroPersonas; ++i) {
        QString nombre;
        int numTags, numTablets;
        in >> nombre >> numTags >> numTablets;

        // Celular
        float celX, celY, rapidez, angulo, deltaAngulo;
        in >> celX >> celY >> rapidez >> angulo >> deltaAngulo;

        Celular* nuevoCelular = new Celular(nombre, celX, celY, rapidez, angulo, deltaAngulo);
        CelularView* vistaCelular = new CelularView(nuevoCelular);
        miTerritorioVisual->addEquipoVisual(vistaCelular);

        // Tags
        for (int j = 0; j < numTags; ++j) {
            QString tagName;
            float tagX, tagY, tagRap, tagAng, tagDeltaAng;
            in >> tagName >> tagX >> tagY >> tagRap >> tagAng >> tagDeltaAng;

            EloTelTag* nuevoTag = new EloTelTag(tagName, nombre, tagX, tagY, tagRap, tagAng, tagDeltaAng);
            EloTelTagView* vistaTag = new EloTelTagView(nuevoTag);
            // Pasar la lista de equipos para que el tag pueda buscar celulares
            vistaTag->setListaEquipos(miTerritorioVisual->getListaEquipos());
            miTerritorioVisual->addEquipoVisual(vistaTag);
        }

        // Tablets
        for (int j = 0; j < numTablets; ++j) {
            float tabX, tabY, tabRap, tabAng, tabDeltaAng;
            in >> tabX >> tabY >> tabRap >> tabAng >> tabDeltaAng;

            Tablet* nuevaTablet = new Tablet("Tablet de " + nombre, nombre, tabX, tabY, tabRap, tabAng, tabDeltaAng);
            TabletView* vistaTablet = new TabletView(nuevaTablet);
            vistaTablet->setListaEquipos(miTerritorioVisual->getListaEquipos());
            miTerritorioVisual->addEquipoVisual(vistaTablet);
        }
    }
}
