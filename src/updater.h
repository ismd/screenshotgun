#ifndef UPDATER_H
#define UPDATER_H

#include <QString>

class Updater
{
public:
    void update(const QByteArray&);
    void copyNew(const QString&);
};

#endif // UPDATER_H
