#include <QGraphicsSceneMouseEvent>
#include "../SceneManager.h"
#include "VisibleAreaRect.h"
#include "VisibleAreaMode.h"

VisibleAreaRect::VisibleAreaRect(VisibleAreaMode& visibleAreaMode, ResizeDirection direction)
    : visibleAreaMode_(visibleAreaMode),
      resizeDirection_(direction),
      sceneManager_(visibleAreaMode_.scene().sceneManager()) {
}

void VisibleAreaRect::mousePressEvent(QGraphicsSceneMouseEvent* e) {
    if (sceneManager_.mode() == sceneManager_.visibleAreaMode()) {
        QGraphicsRectItem::mousePressEvent(e);
    } else {
        visibleAreaMode_.toolbar().hide();
    }
}

void VisibleAreaRect::mouseMoveEvent(QGraphicsSceneMouseEvent* e) {
    if (sceneManager_.mode() == sceneManager_.visibleAreaMode()) {
        QGraphicsRectItem::mouseMoveEvent(e);
    } else {
        resize(e->scenePos(), e->lastScenePos());
    }
}

void VisibleAreaRect::mouseReleaseEvent(QGraphicsSceneMouseEvent* e) {
    if (sceneManager_.mode() == sceneManager_.visibleAreaMode()) {
        QGraphicsRectItem::mouseReleaseEvent(e);
    } else {
        visibleAreaMode_.updateToolbarPosition();
        visibleAreaMode_.toolbar().show();
    };
}

void VisibleAreaRect::resize(QPointF pos, QPointF lastPos) {
    int diffX = pos.x() - lastPos.x();
    int diffY = pos.y() - lastPos.y();

    switch (resizeDirection_) {
        case ResizeDirection::TOP_LEFT:
            visibleAreaMode_.resizeArea(diffX, diffY, 0, 0);
            break;

        case ResizeDirection::LEFT:
            visibleAreaMode_.resizeArea(diffX, 0, 0, 0);
            break;

        case ResizeDirection::BOTTOM_LEFT:
            visibleAreaMode_.resizeArea(diffX, 0, 0, diffY);
            break;

        case ResizeDirection::TOP:
            visibleAreaMode_.resizeArea(0, diffY, 0, 0);
            break;

        case ResizeDirection::BOTTOM:
            visibleAreaMode_.resizeArea(0, 0, 0, diffY);
            break;

        case ResizeDirection::TOP_RIGHT:
            visibleAreaMode_.resizeArea(0, diffY, diffX, 0);
            break;

        case ResizeDirection::RIGHT:
            visibleAreaMode_.resizeArea(0, 0, diffX, 0);
            break;

        case ResizeDirection::BOTTOM_RIGHT:
            visibleAreaMode_.resizeArea(0, 0, diffX, diffY);
            break;
    }
}
