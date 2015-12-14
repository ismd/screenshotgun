#include <QDateTime>
#include "ServiceHelper.h"

QString ServiceHelper::generateFilename() {
    return QDateTime::currentDateTime().toString("yyyy-MM-dd")
           + "_" + QString::number(QDateTime::currentMSecsSinceEpoch()) + ".png";
}
