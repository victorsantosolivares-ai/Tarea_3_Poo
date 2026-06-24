#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QGraphicsPixmapItem>
#include <QFileInfo>

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
    , miTerritorioVisual(nullptr) // Inicializamos en null
    , relojSimulacion(new QTimer(this)) // Inicializamos el reloj
{
    ui->setupUi(this);

    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Seleccionar archivo de configuración", "", "Text Files (*.txt);;All Files (*)");

    if (!fileName.isEmpty()) {
        loadConfiguration(fileName);

        miTerritorioVisual->setDeltaTiempo(deltaTiempo);

        // Conectamos el reloj a una función que crearemos en TerritoryView llamada updateSimulation
        connect(relojSimulacion, &QTimer::timeout, miTerritorioVisual, &TerritoryView::updateSimulation);

        // Multiplicamos por 1000 porque deltaTiempo está en segundos y QTimer usa milisegundos
        relojSimulacion->start(deltaTiempo * 1000);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadConfiguration(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    QTextStream in(&file);

    // 1. Configurar y crear el Territory y TerritoryView
    QString backgroundFileName = in.readLine().trimmed();
    QFileInfo fileInfo(filePath);
    QString imagePath = fileInfo.absolutePath() + "/" + backgroundFileName;

    Territory* territorioModelo = new Territory(imagePath);
    miTerritorioVisual = new TerritoryView(territorioModelo, this);

    // Conectar nuestra vista personalizada a la interfaz gráfica
    ui->graphicsView->setScene(miTerritorioVisual);

    // 2. Leer resto de configuracion
    in >> deltaTiempo;

    int numeroPersonas;
    in >> numeroPersonas;

    // 3. Crear celulares y añadirlos al TerritoryView
    for (int i = 0; i < numeroPersonas; ++i) {
        QString nombre;
        int numTags;
        int numTablets;

        in >> nombre >> numTags >> numTablets;

        float celX, celY, rapidez, angulo, deltaAngulo;
        in >> celX >> celY >> rapidez >> angulo >> deltaAngulo;
        
        Celular* nuevoCelular = new Celular(nombre, celX, celY, rapidez, angulo, deltaAngulo);
        CelularView* vistaCelular = new CelularView(nuevoCelular);

        miTerritorioVisual->addEquipoVisual(vistaCelular); // Añadir al TerritoryView

        // 2. Leer y crear Tags
        for (int j = 0; j < numTags; ++j) {
            QString tagName;
            float tagX, tagY, tagRap, tagAng, tagDeltaAng;
            in >> tagName >> tagX >> tagY >> tagRap >> tagAng >> tagDeltaAng;

            EloTelTag* nuevoTag = new EloTelTag(tagName, tagX, tagY, tagRap, tagAng, tagDeltaAng);
            EloTelTagView* vistaTag = new EloTelTagView(nuevoTag);

            // USAR LA NUEVA FUNCIÓN AQUÍ TAMBIÉN
            miTerritorioVisual->addEquipoVisual(vistaTag);
        }

        // 3. Leer y crear Tablet
        for (int j = 0; j < numTablets; ++j) {
            float tabX, tabY, tabRap, tabAng, tabDeltaAng;
            in >> tabX >> tabY >> tabRap >> tabAng >> tabDeltaAng;

            Tablet* nuevaTablet = new Tablet("Tablet de " + nombre, tabX, tabY, tabRap, tabAng, tabDeltaAng);
            TabletView* vistaTablet = new TabletView(nuevaTablet);

            // Y USAR LA NUEVA FUNCIÓN AQUÍ
            miTerritorioVisual->addEquipoVisual(vistaTablet);
        }
    }
}
