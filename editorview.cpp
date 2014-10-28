#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>
#include "editorview.h"

EditorView::EditorView() : QGraphicsView(), _trayIcon(new QSystemTrayIcon(this)), _scene(NULL), _editorForm(NULL)
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
    delete _scene;
}

QGraphicsScene* EditorView::scene()
{
    return _scene;
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
    // FIXME: need editor form or server signal
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
