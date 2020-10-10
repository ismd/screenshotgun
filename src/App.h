#pragma once

#include "ui/Toolbar.h"

#include <QGraphicsPixmapItem>

#if defined(Q_OS_LINUX)
#include "qxt/qxtglobalshortcut.h"
#endif

class App : public QObject {
    Q_OBJECT

public:
    App();

signals:
    void screenshotFinished(bool);

private slots:
    void makeScreenshot();
    void processScreenshot();
    void cancelScreenshot();

private:
    QGraphicsPixmapItem* pixmap; // Screenshot

    void initShortcut(const QKeySequence);

#if defined(Q_OS_LINUX)
    void initShortcutLinux(const QKeySequence);
#elif defined(Q_OS_WIN32)
    void initShortcutWindows();
#endif

#if defined(Q_OS_LINUX)
    QxtGlobalShortcut shortcut_;
#elif defined(Q_OS_WIN32)
    bool nativeEvent(const QByteArray& eventType, void* message, long* result);
#endif
};
