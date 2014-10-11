#include "editorview.h"

EditorView::EditorView() : QGraphicsView(), editorForm(NULL), mode(NULL)
{
    this->setFrameShape(QFrame::NoFrame);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Making screenshot
    screenshot = QGuiApplication::primaryScreen()->grabWindow(QApplication::desktop()->winId());
    this->setGeometry(0, 0, screenshot.width(), screenshot.height());

    scene = new QGraphicsScene(this);

    // Background screenshot
    scene->addPixmap(screenshot);

    this->setScene(scene);
    visibleArea = new VisibleArea(scene);

    mode = new VisibleAreaMode(visibleArea);
}

void EditorView::mousePressEvent(QMouseEvent *e)
{
    if (NULL != editorForm) {
        delete editorForm;
    }

    mode->mousePress(e);
}

void EditorView::mouseMoveEvent(QMouseEvent *e)
{
    mode->mouseMove(e);
}

void EditorView::mouseReleaseEvent(QMouseEvent *e)
{
    mode->mouseRelease(e);

    editorForm = new EditorForm(this, mode, visibleArea);
    editorForm->setGeometry(visibleArea->getX(), visibleArea->getY() + visibleArea->getHeight() + 5, editorForm->width(), editorForm->height());
    editorForm->show();
}

AbstractMode* EditorView::getMode()
{
    return mode;
}

void EditorView::setMode(AbstractMode *mode)
{
    if (NULL != mode) {
        delete mode;
    }

    this->mode = mode;
}

VisibleArea* EditorView::getVisibleArea()
{
    return visibleArea;
}
