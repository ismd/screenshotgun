#ifndef SCREENSHOTGUN_APP_H
#define SCREENSHOTGUN_APP_H

#include "AppView.h"
#include "History.h"
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
    History& history();
#if defined(Q_OS_WIN32)
    Updater& updater();
#endif
    void setCopyImageToClipboard(bool);

private slots:
    void makeScreenshot();
    void connectionSuccess();
    void connectionError();
    void uploadSuccess(const QString&);
    void uploadError();
    void updateAvailable(const QString&);

private:
    AppView appView_;
    Settings settings_;
    TrayIcon trayIcon_;
    History history_;
    SettingsForm settingsForm_;
    Server server_;
#if defined(Q_OS_WIN32)
    Updater updater_;
#endif
    bool copyImageToClipboard_;
};

#endif // SCREENSHOTGUN_APP_H
