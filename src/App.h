#ifndef SCREENSHOTGUN_APP_H
#define SCREENSHOTGUN_APP_H

#include "History.h"
#include "Overlay.h"
#include "services/Dropbox.h"
#include "services/Server.h"
#include "services/Yandex.h"
#include "services/Google.h"
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
    UploadService uploadService() const;
    Server& server();
    Dropbox& dropbox();
    Yandex& yandex();
    Google& google();
    Settings& settings();
    History& history();
    TrayIcon& trayIcon();
#if defined(Q_OS_WIN32)
    Updater& updater();
#endif
    void setUploadService(UploadService);
    void setCopyImageToClipboard(bool);
    void setConnectionChecks(int);
    bool connected() const;

protected:
    void timerEvent(QTimerEvent*);

private slots:
    void makeScreenshot();
    void connectionSuccess();
    void connectionError();
    void uploadSuccess(const QString&);
    void uploadError();
    void uploadError(QString);
    void updateAvailable(const QString&);
    void openUrl();

private:
    Overlay overlay_;
    Settings settings_;
    TrayIcon trayIcon_;
    History history_;
    UploadService service_;
    Server server_;
    Dropbox dropbox_;
    Yandex yandex_;
    Google google_;
    SettingsForm settingsForm_;
#if defined(Q_OS_WIN32)
    Updater updater_;
#endif
    bool copyImageToClipboard_;
    int connectionChecks_;
    bool connected_;
    QString lastUrl_;
};

#endif // SCREENSHOTGUN_APP_H
