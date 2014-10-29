#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>
#include <QWindow>
#include "editorview.h"

EditorView::EditorView()
    : QGraphicsView(), _scene(new QGraphicsScene(this)), _editorForm(NULL), _trayIcon(new QSystemTrayIcon(this)), _settings(new QSettings("openscreencloud"))
{
    setFrameShape(QFrame::NoFrame);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    setScene(_scene);

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
    // Making screenshot
    //_screenshot = QGuiApplication::focusWindow()->screen()->grabWindow(QGuiApplication::focusWindow()->winId());;
    //_screenshot = QGuiApplication::primaryScreen()->grabWindow(QGuiApplication::focusWindow()->winId());
    _screenshot = QGuiApplication::primaryScreen()->grabWindow(QApplication::desktop()->winId());

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
