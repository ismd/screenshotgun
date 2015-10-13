#include <QApplication>
#include "editorview.h"
#include "trayicon.h"

TrayIcon::TrayIcon(EditorView *parent) :
    _editorView(parent),
    QSystemTrayIcon(parent),
    _makeScreenshotAction(new QAction(tr("&Make screenshot"), this)),
    _settingsAction(new QAction(tr("&Settings"), this)),
    _quitAction(new QAction(tr("&Quit"), this))
{
    connect(_makeScreenshotAction, SIGNAL(triggered()),
            this, SLOT(makeScreenshotAction()));

    connect(_settingsAction, SIGNAL(triggered()),
            this, SLOT(showSettings()));

    connect(_quitAction, SIGNAL(triggered()),
            qApp, SLOT(quit()));

    #ifdef Q_OS_WIN32
    setIcon(QIcon(":/icons/icon-16.png"));
    #elif defined(Q_OS_LINUX)
    setIcon(QIcon(":/icons/icon-22.png"));
    #endif

    setToolTip("Screenshotgun");

    _iconMenu = new QMenu();
    _iconMenu->addAction(_makeScreenshotAction);
    _iconMenu->addAction(_settingsAction);
    _iconMenu->addAction(_quitAction);

    setContextMenu(_iconMenu);
}

TrayIcon::~TrayIcon()
{
    delete _iconMenu;
}

void TrayIcon::makeScreenshotAction()
{
    emit makeScreenshot();
}

void TrayIcon::showSettings()
{
    _editorView->settingsForm()->show();
}
