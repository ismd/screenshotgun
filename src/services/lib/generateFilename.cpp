#include "generateFilename.h"

#include <QDateTime>

QString generateFilename() {
    return QDateTime::currentDateTime().toString("yyyy-MM-dd") + "_"
        + QString::number(QDateTime::currentMSecsSinceEpoch()) + ".png";
}
