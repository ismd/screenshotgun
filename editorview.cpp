#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>

#include "editorview.h"

EditorView::EditorView() : QGraphicsView()
{
    setFrameShape(QFrame::NoFrame);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Making screenshot
    screenshot = QGuiApplication::primaryScreen()->grabWindow(QApplication::desktop()->winId());
    setGeometry(0, 0, screenshot.width(), screenshot.height());

    scene = new QGraphicsScene(this);

    // Background screenshot
    scene->addPixmap(screenshot);

    setScene(scene);
    editorForm = new EditorForm(this, scene);
}

EditorView::~EditorView()
{
    delete scene;
}

void EditorView::mousePressEvent(QMouseEvent *e)
{
    editorForm->getMode()->init(e->x(), e->y());
}

void EditorView::mouseMoveEvent(QMouseEvent *e)
{
    editorForm->getMode()->move(e->x(), e->y());
}

void EditorView::mouseReleaseEvent(QMouseEvent *e)
{
    editorForm->getMode()->stop(e->x(), e->y());
}
