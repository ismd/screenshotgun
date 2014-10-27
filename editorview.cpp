#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>
#include "editorview.h"

EditorView::EditorView() : QGraphicsView()
{
    setFrameShape(QFrame::NoFrame);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    // Making screenshot
    _screenshot = QGuiApplication::primaryScreen()->grabWindow(QApplication::desktop()->winId());
    setGeometry(0, 0, _screenshot.width(), _screenshot.height());

    _scene = new QGraphicsScene(this);

    // Background screenshot
    _scene->addPixmap(_screenshot);

    setScene(_scene);
    _editorForm = new EditorForm(this);
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
