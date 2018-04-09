#include <QDir>
#include "System.h"

System::System() : lockFile_(QDir::temp().absoluteFilePath("screenshotgun.lock")) {
}

System::~System() {
    lockFile_.unlock();
}

bool System::isLaunched() {
    return !lockFile_.tryLock(100);
}
