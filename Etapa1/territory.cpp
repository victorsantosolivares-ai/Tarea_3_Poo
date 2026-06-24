#include "territory.h"

Territory::Territory(QString bgPath) : backgroundImagePath(bgPath) {}

QString Territory::getBackgroundImagePath() const {
    return backgroundImagePath;
}
