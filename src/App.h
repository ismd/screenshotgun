#pragma once

#include <QObject>

#if defined(Q_OS_LINUX)
#include "qxt/qxtglobalshortcut.h"
#endif

class App : public QObject {
    Q_OBJECT

public:
    App();

private slots:
    void makeScreenshot();

private:
#if defined(Q_OS_LINUX)
    void initShortcutLinux();
#elif defined(Q_OS_WIN32)
    void initShortcutWindows();
#endif

#if defined(Q_OS_LINUX)
    QxtGlobalShortcut shortcut_;
#elif defined(Q_OS_WIN32)
    bool nativeEvent(const QByteArray& eventType, void* message, long* result);
#endif
};
