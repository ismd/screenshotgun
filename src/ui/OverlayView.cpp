#include "OverlayView.h"
#include "src/Context.h"

#include <QOpenGLWidget>
#include <QtGlobal>
#include <QScreen>

OverlayView::OverlayView()
    : usingMode_(false),
      movingItem_(false)
{
    setWindowFlags(
        Qt::BypassWindowManagerHint |
        Qt::FramelessWindowHint |
        // Qt::NoDropShadowWindowHint |
        Qt::Tool |
        // Qt::WindowOverridesSystemGestures |
        Qt::WindowStaysOnTopHint |
        Qt::X11BypassWindowManagerHint
    );

    setWindowModality(Qt::ApplicationModal);
    setFocusPolicy(Qt::StrongFocus);

    setFrameShape(QFrame::NoFrame);
    setRenderHints(QPainter::Antialiasing | QPainter::LosslessImageRendering | QPainter::TextAntialiasing);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setScene(&scene);
    setMouseTracking(true);
    setViewport(new QOpenGLWidget);
}

// void OverlayView::reinitVisibleArea() {
//     delete visibleAreaMode_;

//     QPoint position = QCursor::pos();
//     QScreen* screen = QGuiApplication::screenAt(QCursor::pos());
//     QRect geo = screen->geometry();

//     visibleAreaMode_ = new VisibleAreaMode(overlay_, geo.width(), geo.height(), position - geo.topLeft());
//     currentMode_ = visibleAreaMode_;
//     overlay_.toolbar().select(ToolbarMode::VISIBLE_AREA);
// }

// bool OverlayView::movingItem() const {
//     return movingItem_;
// }

// void OverlayView::setMovingItem(bool value) {
//     movingItem_ = value;
// }

// void OverlayView::setCursor(const QCursor& cursor) {
//     overlay_.setCursor(cursor);
// }

// void OverlayView::showEvent(QShowEvent* e) {
//     Context& ctx = Context::getInstance();

//     setGeometry(0, 0, ctx.overlay.width(), ctx.overlay.height());
//     raise();
//     repaint();
//     activateWindow();

//     ctx.overlay.toolbar.raise();
// }

// void OverlayView::mousePressEvent(QMouseEvent* e) {
//     QGraphicsView::mousePressEvent(e);

//     if (movingItem_) {
//         return;
//     }

//     // int x = e->x();
//     // int y = e->y();

//     // if (currentMode_ != visibleAreaMode_
//     //     && visibleAreaMode_->initialized()
//     //     && visibleAreaMode_->isResizablePosition(x, y))
//     // {
//     //     visibleAreaMode_->resizeInit(x, y);
//     //     return;
//     // }

//     usingMode_ = true;
//     // currentMode_->init(x, y);
// }

// void OverlayView::mouseMoveEvent(QMouseEvent* e) {
//     if (Context::getInstance().overlay.isHidden()) {
//         // setMovingItem(false);
//         return;
//     }

//     activateWindow();
//     setFocus();

//     QGraphicsView::mouseMoveEvent(e);

//     if (movingItem_) {
//         return;
//     }

//     // int x = e->x();
//     // int y = e->y();

//     // if (visibleAreaMode_->resizing()) {
//     //     visibleAreaMode_->resizeMove(x, y);
//     // } else if (usingMode_ || (currentMode_ == visibleAreaMode_ && !visibleAreaMode_->initialized())) {
//     //     currentMode_->move(x, y);
//     // } else if (currentMode_ != visibleAreaMode_ && visibleAreaMode_->isResizablePosition(x, y)) {
//     //     switch (visibleAreaMode_->resizablePosition(x, y)) {
//     //         case ResizeDirection::TOP:
//     //         case ResizeDirection::BOTTOM:
//     //             setCursor(Qt::SizeVerCursor);
//     //             break;

//     //         case ResizeDirection::LEFT:
//     //         case ResizeDirection::RIGHT:
//     //             setCursor(Qt::SizeHorCursor);
//     //             break;

//     //         case ResizeDirection::TOP_LEFT:
//     //         case ResizeDirection::BOTTOM_RIGHT:
//     //             setCursor(Qt::SizeFDiagCursor);
//     //             break;

//     //         case ResizeDirection::TOP_RIGHT:
//     //         case ResizeDirection::BOTTOM_LEFT:
//     //             setCursor(Qt::SizeBDiagCursor);
//     //             break;

//     //         case ResizeDirection::NONE:
//     //             break;
//     //     }
//     // } else if (currentMode_ == &textMode_) {
//     //     setCursor(Qt::IBeamCursor);
//     // } else {
//     //     setCursor(Qt::CrossCursor);
//     // }
// }

// void OverlayView::mouseReleaseEvent(QMouseEvent* e) {
//     if (movingItem_) {
//         QGraphicsView::mouseReleaseEvent(e);
//         return;
//     }

//     // int x = e->x();
//     // int y = e->y();

//     // if (visibleAreaMode_->resizing()) {
//     //     visibleAreaMode_->resizeStop(x, y);
//     //     return;
//     // }

//     // currentMode_->stop(x, y);

//     // if (currentMode_ != visibleAreaMode_) {
//     //     usingMode_ = false;
//     // }
// }

void OverlayView::keyReleaseEvent(QKeyEvent* e) {
    int key = e->key();

    switch (key) {
        case Qt::Key_Escape:
            hide();
            break;

        case Qt::Key_Return:
            emit enterClicked();
            break;
    }

    QWidget::keyReleaseEvent(e);
}

// void OverlayView::wheelEvent(QWheelEvent* e) {
//     Context& ctx = Context::getInstance();

//     if (e->angleDelta().y() < 0) {
//         ctx.overlay.toolbar.selectNext();
//     } else {
//         ctx.overlay.toolbar.selectPrevious();
//     }
// }
