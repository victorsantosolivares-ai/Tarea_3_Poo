#ifndef ETNUBE_H
#define ETNUBE_H

#include <QString>
#include <QList>
#include <QDateTime>
#include <QPointF>

struct ReporteEquipo {
    QString nombreEquipo;
    QString duenioEquipo;
    QString duenioCelular;
    float x;
    float y;
    QDateTime timestamp;
    QList<QPointF> historial; // todas las posiciones detectadas
};

class ETNube {
public:
    static ETNube& instancia() {
        static ETNube nube;
        return nube;
    }

    void reportar(const QString& nombreEquipo, const QString& duenioEquipo,
                  const QString& duenioCelular, float x, float y)
    {
        for (ReporteEquipo& r : reportes) {
            if (r.nombreEquipo == nombreEquipo) {
                r.duenioCelular = duenioCelular;
                r.x = x;
                r.y = y;
                r.timestamp = QDateTime::currentDateTime();
                r.historial.append(QPointF(x, y));
                return;
            }
        }
        ReporteEquipo nuevo;
        nuevo.nombreEquipo = nombreEquipo;
        nuevo.duenioEquipo = duenioEquipo;
        nuevo.duenioCelular = duenioCelular;
        nuevo.x = x;
        nuevo.y = y;
        nuevo.timestamp = QDateTime::currentDateTime();
        nuevo.historial.append(QPointF(x, y));
        reportes.append(nuevo);
    }

    QList<ReporteEquipo> obtenerEquiposDe(const QString& duenio) const {
        QList<ReporteEquipo> resultado;
        for (const ReporteEquipo& r : reportes)
            if (r.duenioEquipo == duenio)
                resultado.append(r);
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
