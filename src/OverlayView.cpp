#include <QDesktopWidget>
#include "App.h"
#include "Overlay.h"
#include "OverlayView.h"

OverlayView::OverlayView(QWidget* parent, Overlay& overlay)
    : QGraphicsView(parent),
      overlay_(overlay),
      visibleAreaMode_(nullptr),
      lineMode_(overlay_),
      arrowMode_(overlay_),
      rectMode_(overlay_),
      ellipseMode_(overlay_),
      textMode_(overlay_),
      usingMode_(false),
      movingItem_(false) {
    setFrameShape(QFrame::NoFrame);
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    scene_.setItemIndexMethod(QGraphicsScene::NoIndex);
    setScene(&scene_);

    setMouseTracking(true);
}

OverlayView::~OverlayView() {
    delete visibleAreaMode_;
}

QGraphicsScene& OverlayView::scene() {
    return scene_;
}

VisibleAreaMode& OverlayView::visibleAreaMode() const {
    return *visibleAreaMode_;
}

void OverlayView::setMode(const ToolbarMode mode) {
    switch (mode) {
        case ToolbarMode::VISIBLE_AREA:
            currentMode_ = visibleAreaMode_;
            break;

        case ToolbarMode::LINE:
            currentMode_ = &lineMode_;
            overlay_.app().history().setLastTool(ToolbarMode::LINE);
            break;

        case ToolbarMode::ARROW:
            currentMode_ = &arrowMode_;
            overlay_.app().history().setLastTool(ToolbarMode::ARROW);
            break;

        case ToolbarMode::RECT:
            currentMode_ = &rectMode_;
            overlay_.app().history().setLastTool(ToolbarMode::RECT);
            break;

        case ToolbarMode::ELLIPSE:
            currentMode_ = &ellipseMode_;
            overlay_.app().history().setLastTool(ToolbarMode::ELLIPSE);
            break;

        case ToolbarMode::TEXT:
            currentMode_ = &textMode_;
            overlay_.app().history().setLastTool(ToolbarMode::TEXT);
            break;
    }
}

void OverlayView::reinitVisibleArea() {
    delete visibleAreaMode_;

    QDesktopWidget* desktop = QApplication::desktop();
    QRect geo = desktop->screenGeometry(desktop->screenNumber(QCursor::pos()));

    visibleAreaMode_ = new VisibleAreaMode(overlay_, geo.width(), geo.height());
    currentMode_ = visibleAreaMode_;
    overlay_.toolbar().select(ToolbarMode::VISIBLE_AREA);
}

bool OverlayView::movingItem() const {
    return movingItem_;
}

void OverlayView::setMovingItem(bool value) {
    movingItem_ = value;
}

void OverlayView::setCursor(const QCursor& cursor) {
    overlay_.setCursor(cursor);
}

void OverlayView::showEvent(QShowEvent* e) {
    setGeometry(0, 0, overlay_.width(), overlay_.height());
    raise();
    repaint();
    activateWindow();

    overlay_.toolbar().raise();
}

void OverlayView::mousePressEvent(QMouseEvent* e) {
    QGraphicsView::mousePressEvent(e);

    if (movingItem_) {
        return;
    }

    int x = e->x();
    int y = e->y();

    if (currentMode_ != visibleAreaMode_
        && visibleAreaMode_->initialized()
        && visibleAreaMode_->isResizablePosition(x, y))
    {
        visibleAreaMode_->resizeInit(x, y);
        return;
    }

    usingMode_ = true;
    currentMode_->init(x, y);
}

void OverlayView::mouseMoveEvent(QMouseEvent* e) {
    QGraphicsView::mouseMoveEvent(e);

    if (movingItem_) {
        return;
    }

    int x = e->x();
    int y = e->y();

    if (visibleAreaMode_->resizing()) {
        visibleAreaMode_->resizeMove(x, y);
    } else if (usingMode_ || currentMode_ == visibleAreaMode_ && !visibleAreaMode_->initialized()) {
        currentMode_->move(x, y);
    } else if (currentMode_ != visibleAreaMode_ && visibleAreaMode_->isResizablePosition(x, y)) {
        switch (visibleAreaMode_->resizablePosition(x, y)) {
            case ResizeDirection::TOP:
            case ResizeDirection::BOTTOM:
                setCursor(Qt::SizeVerCursor);
                break;

            case ResizeDirection::LEFT:
            case ResizeDirection::RIGHT:
                setCursor(Qt::SizeHorCursor);
                break;

            case ResizeDirection::TOP_LEFT:
            case ResizeDirection::BOTTOM_RIGHT:
                setCursor(Qt::SizeFDiagCursor);
                break;

            case ResizeDirection::TOP_RIGHT:
            case ResizeDirection::BOTTOM_LEFT:
                setCursor(Qt::SizeBDiagCursor);
                break;
        }
    } else if (currentMode_ == &textMode_) {
        setCursor(Qt::IBeamCursor);
    } else {
        setCursor(Qt::CrossCursor);
    }
}

void OverlayView::mouseReleaseEvent(QMouseEvent* e) {
    if (movingItem_) {
        QGraphicsView::mouseReleaseEvent(e);
        return;
    }

    int x = e->x();
    int y = e->y();

    if (visibleAreaMode_->resizing()) {
        visibleAreaMode_->resizeStop(x, y);
        return;
    }

    currentMode_->stop(x, y);

    if (currentMode_ != visibleAreaMode_) {
        usingMode_ = false;
    }
}

void OverlayView::keyReleaseEvent(QKeyEvent* e) {
    int key = e->key();

    if (key == Qt::Key_Escape) {
        overlay_.hide();
    } else if (key == Qt::Key_Return) {
        if (currentMode_ != &textMode_ || textMode_.textArea() == 0 || !textMode_.textArea()->hasFocus()) {
            overlay_.app().setCopyImageToClipboard(e->modifiers().testFlag(Qt::AltModifier));
            overlay_.toolbar().submit();
        }
    }

    QWidget::keyReleaseEvent(e);
}

void OverlayView::wheelEvent(QWheelEvent* e) {
    if (e->delta() < 0) {
        overlay_.toolbar().setSelectedNext();
    } else {
        overlay_.toolbar().setSelectedPrevious();
    }
}
