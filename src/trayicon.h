#ifndef TRAYICON_H
#define TRAYICON_H

#include <QSystemTrayIcon>
#include <QAction>
#include <QMenu>

class TrayIcon : public QSystemTrayIcon
{
    Q_OBJECT

public:
    explicit TrayIcon(QObject *parent);
    ~TrayIcon();

private:
    QMenu* _iconMenu;
    QAction* _quitAction;
};

#endif // TRAYICON_H
