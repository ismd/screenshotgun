#ifndef SCREENSHOTGUN_APP_H
#define SCREENSHOTGUN_APP_H

#include "AppView.h"
#include "Server.h"
#include "Settings.h"
#include "SettingsForm.h"
#include "TrayIcon.h"

#if defined(Q_OS_LINUX)
    #include "qxtglobalshortcut.h"
#endif

class App : public QObject {
    Q_OBJECT

public:
    App();

    SettingsForm& settingsForm();
    Server& server();

private slots:
    void makeScreenshot();
    void uploadSuccess(QString);
    void uploadError();

private:
    AppView appView_;
    TrayIcon trayIcon_;
    SettingsForm settingsForm_;
    Server server_;

#ifdef Q_OS_WIN32
    nativeEvent(const QByteArray& eventType, void* message, long* result);
#elif defined(Q_OS_LINUX)
    QxtGlobalShortcut shortcut_;
#endif
};

#endif // SCREENSHOTGUN_APP_H
