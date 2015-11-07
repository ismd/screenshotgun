#ifndef SCREENSHOTGUN_APP_H
#define SCREENSHOTGUN_APP_H

#include "AppView.h"
#include "Server.h"
#include "Settings.h"
#include "SettingsForm.h"
#include "TrayIcon.h"

#if defined(Q_OS_WIN32)
#include "Updater_win.h"
#endif

class App : public QObject {
    Q_OBJECT

public:
    App();

    SettingsForm& settingsForm();
    Server& server();
    Settings& settings();
#if defined(Q_OS_WIN32)
    Updater& updater();
#endif

private slots:
    void makeScreenshot();
    void connectionSuccess();
    void connectionError();
    void uploadSuccess(QString);
    void uploadError();

private:
    AppView appView_;
    TrayIcon trayIcon_;
    Settings settings_;
    SettingsForm settingsForm_;
    Server server_;
#if defined(Q_OS_WIN32)
    Updater updater_;
#endif
};

#endif // SCREENSHOTGUN_APP_H
