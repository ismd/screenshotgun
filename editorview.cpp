#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>
#include <QWindow>
#include "editorview.h"
#include "const.h"

EditorView::EditorView() :
    QGraphicsView(),
    _scene(new QGraphicsScene(this)),
    _editorForm(NULL),
    _trayIcon(new QSystemTrayIcon(this)),
    _settings(new Settings(this)),
    _server(new Server(this))
{
    connect(_settings, SIGNAL(valid()),
            this, SLOT(checkVersion()));

    connect(_server, SIGNAL(serverVersion(QString)),
            this, SLOT(serverVersion(QString)));

    connect(_server, SIGNAL(connectionError()),
            this, SLOT(connectionError()));

    connect(_server, SIGNAL(newVersionDownloaded(QByteArray)),
            this, SLOT(newVersionDownloaded(QByteArray)));

    // isValid will send signal `valid'
    if (!_settings->isValid()) {
        _settings->show();
    }
}

EditorView::~EditorView()
{
}

void EditorView::init()
{
    disconnect(_settings, SIGNAL(valid()),
               this, SLOT(checkVersion()));

    setFrameShape(QFrame::NoFrame);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    setScene(_scene);

    _trayIcon->show();
    connect(_trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(run()));
}

QGraphicsScene* EditorView::scene()
{
    return _scene;
}

Settings* EditorView::settings()
{
    return _settings;
}

void EditorView::mousePressEvent(QMouseEvent *e)
{
    _editorForm->mode()->init(e->x(), e->y());
}

void EditorView::mouseMoveEvent(QMouseEvent *e)
{
    _editorForm->mode()->move(e->x(), e->y());
}

void EditorView::mouseReleaseEvent(QMouseEvent *e)
{
    _editorForm->mode()->stop(e->x(), e->y());
}

void EditorView::run()
{
    // Making screenshot
    QDesktopWidget *desktop = QApplication::desktop();
    QRect geo = desktop->screenGeometry(desktop->screenNumber(QCursor::pos()));

    _screenshot = QGuiApplication::primaryScreen()->grabWindow(
                desktop->winId(), geo.left(), geo.top(), geo.width(), geo.height());

    int width = _screenshot.width(),
        height = _screenshot.height();

    setGeometry(0, 0, width, height);
    _scene->clear();
    _scene->setSceneRect(0, 0, width, height);

    // Background screenshot
    _scene->addPixmap(_screenshot);

    if (NULL != _editorForm) {
        delete _editorForm;
    }

    _editorForm = new EditorForm(this);
    showFullScreen();
}

void EditorView::checkVersion()
{
    _server->setUrl(_settings->server());
    _server->version();
}

void EditorView::serverVersion(QString version)
{
    if (VERSION != version) {
        _server->downloadNewVersion();
        return;
    }

    _settings->setError("")->hide();
    init();
}

void EditorView::connectionError()
{
    _settings->setError(QString("Can't connect to server"))->show();
}

void EditorView::newVersionDownloaded(QByteArray file)
{
    QString path = QApplication::applicationDirPath();

    QString newFilename = path + "/open-screen-cloud-new";
    QFile newFile(newFilename);

    newFile.open(QIODevice::WriteOnly);
    newFile.write(file);
    newFile.setPermissions(QFile::ReadOwner|QFile::WriteOwner|QFile::ExeOwner|QFile::ReadGroup|QFile::ExeGroup|QFile::ReadOther|QFile::ExeOther);
    newFile.close();

    QProcess::startDetached(newFilename);
    exit(12);
}
