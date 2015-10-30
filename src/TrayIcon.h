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

signals:
    void makeScreenshot();

private slots:
    void trayActivated(QSystemTrayIcon::ActivationReason);
    void makeScreenshotSlot();
    void showSettings();

private:
    App& app_;
    QMenu iconMenu_;
    QAction makeScreenshotAction_;
    QAction settingsAction_;
    QAction quitAction_;
};

#endif // SCREENSHOTGUN_TRAYICON_H
