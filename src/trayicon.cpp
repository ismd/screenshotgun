#include "trayicon.h"
#include <QApplication>

TrayIcon::TrayIcon(QObject *parent) : QSystemTrayIcon(parent)
{
    _quitAction = new QAction(tr("&Quit"), this);
    connect(_quitAction, SIGNAL(triggered()),
            qApp, SLOT(quit()));

    _iconMenu = new QMenu();
    _iconMenu->addAction(_quitAction);

    setContextMenu(_iconMenu);
}

TrayIcon::~TrayIcon()
{
    delete _iconMenu;
}
