#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QGraphicsPixmapItem>
#include "Celular.h"
#include "CelularView.h"
#include "Territory.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , miTerritorioVisual(nullptr) // Inicializamos en null
{
    ui->setupUi(this);

    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Seleccionar archivo de configuración", "", "Text Files (*.txt);;All Files (*)");

    if (!fileName.isEmpty()) {
        loadConfiguration(fileName);
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
    float deltaTiempo;
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

        miTerritorioVisual->addCelularView(vistaCelular); // Añadir al TerritoryView

        // --- Saltar los datos de los Tags por ahora ---
        for (int j = 0; j < numTags; ++j) {
            QString dummyName;
            float dummy1, dummy2, dummy3, dummy4, dummy5;
            in >> dummyName >> dummy1 >> dummy2 >> dummy3 >> dummy4 >> dummy5;
        }

        // --- Saltar los datos de la Tablet por ahora ---
        for (int j = 0; j < numTablets; ++j) {
            float dummy1, dummy2, dummy3, dummy4, dummy5;
            in >> dummy1 >> dummy2 >> dummy3 >> dummy4 >> dummy5;
        }
    }
}
