#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QGraphicsPixmapItem>
#include "Celular.h"
#include "CelularView.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 1. Inicializar la escena gráfica
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene); // Conectar la vista con la escena

    // 2. Pedir al usuario el archivo config.txt usando QFileDialog
    // Esto abrirá la típica ventana de Windows para buscar archivos
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    "Seleccionar archivo de configuración", "", "Text Files (*.txt);;All Files (*)");

    if (fileName.isEmpty()) {
        QMessageBox::warning(this, "Aviso", "No se seleccionó ningún archivo. El programa se cerrará.");
        // Aquí podrías cerrar la aplicación si el archivo es obligatorio
    } else {
        // 3. Procesar el archivo
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

    QString backgroundFileName = in.readLine().trimmed();
    QFileInfo fileInfo(filePath);
    QString imagePath = fileInfo.absolutePath() + "/" + backgroundFileName;

    QPixmap background(imagePath);
    if (!background.isNull()) {
        scene->addPixmap(background);
        scene->setSceneRect(background.rect());
    }

    float deltaTiempo;
    in >> deltaTiempo;

    int numeroPersonas;
    in >> numeroPersonas;

    // --- CICLO PRINCIPAL DE LECTURA ---
    for (int i = 0; i < numeroPersonas; ++i) {
        QString nombre;
        int numTags;
        int numTablets;
        in >> nombre >> numTags >> numTablets;

        // Leer datos del celular de esta persona
        float celX, celY, rapidez, angulo, deltaAngulo;
        in >> celX >> celY >> rapidez >> angulo >> deltaAngulo;

        // 1. Crear el modelo (La lógica)
        Celular* nuevoCelular = new Celular(nombre, celX, celY, rapidez, angulo, deltaAngulo);

        // 2. Crear la vista (Lo visual) pasándole el modelo
        CelularView* vistaCelular = new CelularView(nuevoCelular);

        // 3. Añadir la vista al territorio visual (la escena)
        scene->addItem(vistaCelular);

        // --- Ignorar temporalmente los tags ---
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
