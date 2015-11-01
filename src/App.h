#ifndef SCREENSHOTGUN_APP_H
#define SCREENSHOTGUN_APP_H

#include "AppView.h"
#include "Server.h"
#include "Settings.h"
#include "SettingsForm.h"
#include "TrayIcon.h"

class App : public QObject {
    Q_OBJECT

public:
    App();

    SettingsForm& settingsForm();
    Server& server();
    Settings& settings();

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
};

#endif // SCREENSHOTGUN_APP_H
