#ifndef AUTOSTARTUP_H
#define AUTOSTARTUP_H

#include <QCoreApplication>

class AutoStartup
{
public:
    AutoStartup();
    ~AutoStartup();
    void set(bool);

#ifdef Q_OS_LINUX
    void setLinux(bool);
#endif
};

#endif // AUTOSTARTUP_H
