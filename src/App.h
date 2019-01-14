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
#include "Updater.h"

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
    Updater& updater();
    void setUploadService(UploadService);
    void setCopyImageToClipboard(bool);
    void setConnectionChecks(int);
    bool connected() const;
    void copyImageToClipboard();

protected:
    void timerEvent(QTimerEvent*);

private slots:
    void makeScreenshot();
    void connectionSuccess();
    void connectionError();
    void uploadSuccess(const QString&);
    void uploadError();
    void uploadError(QString);
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
    Updater updater_;
    bool copyImageToClipboard_;
    int connectionChecks_;
    bool connected_;
    QString lastUrl_;
    void initShortcut();
#if defined(Q_OS_LINUX)
    QxtGlobalShortcut shortcut_;
#elif defined(Q_OS_WIN32)
    bool nativeEvent(const QByteArray& eventType, void* message, long* result);
#endif
};

#endif // SCREENSHOTGUN_APP_H
