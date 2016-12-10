#ifndef SCREENSHOTGUN_AUTOSTARTUP_H
#define SCREENSHOTGUN_AUTOSTARTUP_H

class AutoStartup {

public:
    void set(bool);

protected:
#ifdef Q_OS_WIN32
    void setWindows(bool);
#endif

#ifdef Q_OS_LINUX
    void setLinux(bool);
#endif
};

#endif // SCREENSHOTGUN_AUTOSTARTUP_H
