#ifndef UPDATER_H
#define UPDATER_H

#include <QString>

class Updater
{
public:
    Updater();
    ~Updater();
    void update(const QByteArray&);
    void copyNew(const QString&);
};

#endif // UPDATER_H
