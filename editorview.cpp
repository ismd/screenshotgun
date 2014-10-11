#include "editorview.h"

EditorView::EditorView() : QGraphicsView()
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
}

void EditorView::mousePressEvent(QMouseEvent *e)
{
    visibleArea->set(e->x(), e->y(), 0, 0);
}

void EditorView::mouseMoveEvent(QMouseEvent *e)
{
    int x = visibleArea->getX();
    int y = visibleArea->getY();

    int width = visibleArea->getWidth();
    int height = visibleArea->getHeight();

    int curX = e->x();
    int curY = e->y();

    if (curX > x && qAbs(x + width - curX) <= qAbs(x - curX)) {
        width = curX - x;
    } else {
        width = width + x - curX;
        x = curX;
    }

    if (curY > y && qAbs(y + height - curY) <= qAbs(y - curY)) {
        height = curY - y;
    } else {
        height = height + y - curY;
        y = curY;
    }

    visibleArea->set(x, y, width, height);
}
