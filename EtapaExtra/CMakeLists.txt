cmake_minimum_required(VERSION 3.19)
project(Tarea_3_ELO329 LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(Tarea_3_ELO329
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp      mainwindow.h
    mainwindow.ui
    equipo.cpp          equipo.h
    celular.cpp         celular.h
    celularview.cpp     celularview.h
    eloteltag.cpp       eloteltag.h
    eloteltagview.cpp   eloteltagview.h
    tablet.cpp          tablet.h
    tabletview.cpp      tabletview.h
    territory.cpp       territory.h
    territoryview.cpp   territoryview.h
    etnube.h
    findmydialog.cpp    findmydialog.h
    gfindmydialog.cpp   gfindmydialog.h
)

target_link_libraries(Tarea_3_ELO329
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS Tarea_3_ELO329
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Tarea_3_ELO329
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
