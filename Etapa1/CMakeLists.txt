cmake_minimum_required(VERSION 3.19)
project(Tarea_3_Poo LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(Tarea_3_Poo
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    Equipo.h Equipo.cpp
    Celular.h Celular.cpp
    CelularView.h CelularView.cpp
)

target_link_libraries(Tarea_3_Poo
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS Tarea_3_Poo
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Tarea_3_Poo
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
