========================================================================
TAREA 3: SIMULADOR GRÁFICO DE ELOTELTAGS Y APLICACIÓN FIND MY (C++/Qt)
========================================================================
Diseño y Programación Orientados a Objetos (ELO329)
2026-1 Grupo 5

------------------------------------------------------------------------
1. DESCRIPCIÓN PRINCIPAL DEL PROGRAMA
------------------------------------------------------------------------
Este programa es un simulador gráfico interactivo, migrado desde Java/
JavaFX (Tarea 2) a C++ con Qt 6 (Qt Widgets + QGraphicsScene). Su 
función principal es mostrar en un mapa cómo se mueven distintas 
personas llevando consigo equipos de rastreo (Tags), celulares y 
tablets.

A medida que se mueven, los dispositivos simulan buscarse entre sí 
emitiendo señales de radar visuales (un círculo que crece desde el 
equipo hasta 50 píxeles de radio en 1 segundo). Cada EloTelTag y cada 
Tablet busca celulares cercanos cada cierto tiempo (tbip segundos), sin 
sincronizarse entre ellos. Cuando un celular es alcanzado por la señal 
de un Tag o una Tablet, el celular reporta a la nube (ETNube) el 
nombre del dispositivo, su dueño/a y la posición del celular en ese 
momento.

El usuario puede hacer clic en cualquier celular o tablet para abrir 
la herramienta "Find My" y ver, en una tabla que se actualiza cada 
segundo, dónde fue visto por última vez cada uno de sus equipos. 
Además, cada equipo en esa tabla cuenta con un botón de "traza" que 
dibuja en el mapa la trayectoria seguida por ese equipo desde que se 
activó.

------------------------------------------------------------------------
2. ARCHIVOS QUE COMPONEN LA TAREA (ÚLTIMA ETAPA - ETAPA 4 + EXTRA)
------------------------------------------------------------------------
El proyecto en su etapa final se compone de los siguientes archivos:

* Modelos (Lógica y datos):
  - Equipo.h / Equipo.cpp         : Clase base que define posición,
                                     dueño y movimiento (rebote en bordes).
  - Celular.h / Celular.cpp       : Representa el celular de una persona.
  - Tablet.h / Tablet.cpp         : Representa una tablet rastreable,
                                     con dueño/a propio (getDuenio()).
  - EloTelTag.h / EloTelTag.cpp   : Representa un llavero/tag rastreable,
                                     con dueño/a propio (getDuenio()).
  - Territory.h / Territory.cpp   : Guarda la ruta de la imagen de fondo
                                     del mapa.
  - ETNube.h                      : Singleton (header-only) que simula
                                     el servidor en la nube. Guarda la
                                     última posición reportada de cada
                                     equipo y su historial completo de
                                     posiciones (usado para la traza).

* Vistas (Interfaz gráfica):
  - CelularView.h / .cpp          : Dibuja el celular (rectángulo azul),
                                     su radar visual y su menú contextual
                                     (Find My / GFindMy).
  - TabletView.h / .cpp           : Dibuja la tablet (rectángulo verde),
                                     su radar, detecta celulares cercanos
                                     y reporta a ETNube. Incluye también
                                     menú Find My / GFindMy.
  - EloTelTagView.h / .cpp        : Dibuja el tag (círculo rojo), su
                                     radar, detecta celulares cercanos y
                                     reporta a ETNube.
  - TerritoryView.h / .cpp        : QGraphicsScene que dibuja el mapa de
                                     fondo, contiene la lista de todos
                                     los equipos y avanza la simulación
                                     (updateSimulation).
  - FindMyDialog.h / .cpp         : Ventana flotante con tabla de
                                     equipos rastreados de una persona.
                                     Se actualiza cada 1 segundo mientras
                                     está abierta y permite mostrar u
                                     ocultar la traza de cada equipo.
  - GFindMyDialog.h / .cpp        : [EXTRA] Ventana "Graphics Find My":
                                     réplica visual del mapa principal
                                     (misma imagen de fondo) mostrando
                                     solo los equipos de la persona
                                     seleccionada, actualizada cada 1
                                     segundo según la información de
                                     ETNube.

* Principal y Recursos:
  - main.cpp           : Punto de entrada (Main) de la aplicación.
  - mainwindow.h / .cpp / .ui : Ventana principal; lee el archivo de
                                 configuración, crea los equipos y
                                 contiene el menú Simulation (Play/Pause).
  - CMakeLists.txt      : Script de compilación del proyecto (Qt 6 +
                           CMake).
  - config.txt          : (Ejemplo) Archivo de texto con las coordenadas
                           y datos de cada persona/equipo.

------------------------------------------------------------------------
3. CÓMO COMPILAR Y EJECUTAR CADA ETAPA
------------------------------------------------------------------------
Requisito previo: Debe tener instalado Qt 6 (Qt Creator recomendado) 
con el kit "Desktop Qt 6.x MinGW 64-bit" (o el compilador equivalente 
en su sistema operativo).

MÉTODO RECOMENDADO (Qt Creator):
- Abra el archivo 'CMakeLists.txt' desde File > Open File or Project.
- Espere a que Qt Creator configure el proyecto con CMake.
- Presione el botón "Build" (martillo) para compilar.
- Presione "Run" (flecha verde) para ejecutar.

MÉTODO POR LÍNEA DE COMANDOS (Linux / servidor aragorn):
- Para configurar : cmake -S . -B build
- Para compilar    : cmake --build build
- Para ejecutar    : ./build/Tarea_3_ELO329
- Para limpiar      : rm -rf build

Nota: Al ejecutar el programa, se abrirá una ventana pidiendo 
seleccionar un archivo de configuración (ej. config.txt).

------------------------------------------------------------------------
4. BONIFICACIÓN EXTRA (EXTRA-CRÉDITO)
------------------------------------------------------------------------
Se hace entrega de la opción extra GFindMy ("Graphics Find My"). Al 
hacer clic derecho sobre un celular o tablet y seleccionar "GFindMy", 
se abre una ventana independiente con la misma imagen de fondo de la 
simulación principal, mostrando únicamente los equipos (tags y 
tablets) de la persona dueña del dispositivo seleccionado. Las 
posiciones mostradas se actualizan automáticamente cada 1 segundo 
según la última información disponible en ETNube.

------------------------------------------------------------------------
5. DOCUMENTACIÓN ADICIONAL
------------------------------------------------------------------------
* El diagrama de clases (UML) del proyecto se encuentra adjunto como 
  imagen en la carpeta raíz del proyecto.
* No se incluye Javadoc por tratarse de un proyecto en C++; se 
  recomienda comentar el código en español siguiendo el estilo 
  utilizado en los archivos .h y .cpp entregados.
