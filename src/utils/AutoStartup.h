#pragma once

#include <QtGlobal>

class AutoStartup {
public:
    static void set(const bool);

private:
#if defined(Q_OS_LINUX)
    static void setLinux(const bool);
#endif

#if defined(Q_OS_WIN32)
    static void setWindows(const bool);
#endif
};
