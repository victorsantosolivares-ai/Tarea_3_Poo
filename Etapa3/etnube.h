#ifndef ETNUBE_H
#define ETNUBE_H

#include <QString>
#include <QList>
#include <QDateTime>

// Reporte: un tag/tablet de 'duenioEquipo' fue detectado por el celular de 'duenioCelular'
// en la posición (x,y) del celular en ese momento.
struct ReporteEquipo {
    QString nombreEquipo;   // nombre del tag o tablet (ej: "maleta", "Tablet de Pedro")
    QString duenioEquipo;   // dueño del tag/tablet (ej: "Pedro")
    QString duenioCelular;  // dueño del celular que lo detectó (ej: "Pedro" o "Juan")
    float x;                // posición del celular al momento de la detección
    float y;
    QDateTime timestamp;
};

class ETNube {
public:
    static ETNube& instancia() {
        static ETNube nube;
        return nube;
    }

    // llamado cuando un celular (duenioCelular, posX, posY) detecta un tag/tablet
    // cuyo nombre es nombreEquipo y su dueño es duenioEquipo
    void reportar(const QString& nombreEquipo, const QString& duenioEquipo,
                  const QString& duenioCelular, float x, float y)
    {
        for (ReporteEquipo& r : reportes) {
            if (r.nombreEquipo == nombreEquipo) {
                r.duenioCelular = duenioCelular;
                r.x = x;
                r.y = y;
                r.timestamp = QDateTime::currentDateTime();
                return;
            }
        }
        reportes.append({nombreEquipo, duenioEquipo, duenioCelular, x, y,
                         QDateTime::currentDateTime()});
    }

    // Devuelve equipos cuyo dueño es 'duenio' (tags y tablets de esa persona)
    QList<ReporteEquipo> obtenerEquiposDe(const QString& duenio) const {
        QList<ReporteEquipo> resultado;
        for (const ReporteEquipo& r : reportes) {
            if (r.duenioEquipo == duenio)
                resultado.append(r);
        }
        return resultado;
    }

    const QList<ReporteEquipo>& todos() const { return reportes; }

private:
    ETNube() {}
    ETNube(const ETNube&) = delete;
    ETNube& operator=(const ETNube&) = delete;
    QList<ReporteEquipo> reportes;
};

#endif // ETNUBE_H
