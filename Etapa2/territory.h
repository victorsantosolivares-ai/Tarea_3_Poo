#ifndef TERRITORY_H
#define TERRITORY_H
#include <QString>

class Territory {
private:
    QString backgroundImagePath;
public:
    Territory(QString bgPath);
    QString getBackgroundImagePath() const;
};

#endif // TERRITORY_H
