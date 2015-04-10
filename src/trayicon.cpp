#include "trayicon.h"
#include "editorview.h"
#include <QApplication>

TrayIcon::TrayIcon(EditorView *parent) :
    _editorView(parent),
    QSystemTrayIcon(parent),
    _settingsAction(new QAction(tr("&Settings"), this)),
    _quitAction(new QAction(tr("&Quit"), this))
{
    connect(_settingsAction, SIGNAL(triggered()),
            this, SLOT(showSettings()));

    connect(_quitAction, SIGNAL(triggered()),
            qApp, SLOT(quit()));

    _iconMenu = new QMenu();
    _iconMenu->addAction(_settingsAction);
    _iconMenu->addAction(_quitAction);

    setContextMenu(_iconMenu);
}

TrayIcon::~TrayIcon()
{
    delete _iconMenu;
}

void TrayIcon::showSettings()
{
    _editorView->settings()->show();
}
