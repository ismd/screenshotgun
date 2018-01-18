#ifndef SCREENSHOTGUN_TRAYICON_H
#define SCREENSHOTGUN_TRAYICON_H

#include <QAction>
#include <QMenu>
#include <QSystemTrayIcon>

class App;

#ifdef Q_OS_MACOS
bool canOsXSendUserNotification();
void sendOsXUserNotification(const QString &title, const QString &message);
#endif

class TrayIcon : public QSystemTrayIcon {
    Q_OBJECT

public:
    explicit TrayIcon(App&);

    void show();
    void showMessage(const QString& title,
                     const QString& msg,
                     QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::Information,
                     int msecs = 10000);

signals:
    void makeScreenshot();

private slots:
    void trayActivated(QSystemTrayIcon::ActivationReason);
    void makeScreenshotSlot();
    void updateSlot();
    void showSettings();
    void openLink();
    void linkAdded(const QString&);

private:
    App& app_;
    QMenu iconMenu_;
    QAction makeScreenshotAction_;
    QAction updateAction_;
    QAction settingsAction_;
    QMenu historyMenu_;
    QAction quitAction_;
};

#endif // SCREENSHOTGUN_TRAYICON_H
