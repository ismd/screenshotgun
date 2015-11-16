#ifndef SCREENSHOTGUN_TRAYICON_H
#define SCREENSHOTGUN_TRAYICON_H

#include <QAction>
#include <QMenu>
#include <QSystemTrayIcon>

class App;

class TrayIcon : public QSystemTrayIcon {
    Q_OBJECT

public:
    explicit TrayIcon(App&);

    void show();
    void showMessage(const QString& title,
                     const QString& msg,
                     QSystemTrayIcon::MessageIcon icon = QSystemTrayIcon::Information,
                     int msecs = 10000);
    void showError(const QString&, const QString&);

#if defined(Q_OS_WIN32)
    void showNewVersionAvailable(const QString&);
#endif

signals:
    void makeScreenshot();

private slots:
    void trayActivated(QSystemTrayIcon::ActivationReason);
    void makeScreenshotSlot();
    void updateSlot();
    void noUpdate();
    void showSettings();
    void openLink();
    void linkAdded(const QString&);

private:
    App& app_;
    QMenu iconMenu_;
    QAction makeScreenshotAction_;
#if defined(Q_OS_WIN32)
    QAction updateAction_;
#endif
    QAction settingsAction_;
    QMenu historyMenu_;
    QAction quitAction_;
};

#endif // SCREENSHOTGUN_TRAYICON_H
