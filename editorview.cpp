#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>
#include <QMessageBox>
#include "editorview.h"

EditorView::EditorView()
    : QGraphicsView(), _trayIcon(new QSystemTrayIcon(this)), _settings(new QSettings("openscreencloud")), _scene(NULL), _editorForm(NULL)
{
    setFrameShape(QFrame::NoFrame);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    _trayIcon->show();
    connect(_trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
}

EditorView::~EditorView()
{
}

QGraphicsScene* EditorView::scene()
{
    return _scene;
}

QSettings* EditorView::settings()
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

void EditorView::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    if (NULL != _scene) {
        delete _scene;
    }

    if (NULL != _editorForm) {
        delete _editorForm;
    }

    _scene = new QGraphicsScene(this);
    setScene(_scene);

    // Making screenshot
    _screenshot = QGuiApplication::primaryScreen()->grabWindow(QApplication::desktop()->winId());
    setGeometry(0, 0, _screenshot.width(), _screenshot.height());

    // Background screenshot
    _scene->addPixmap(_screenshot);

    _editorForm = new EditorForm(this);
    showFullScreen();
}
