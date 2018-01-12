#include <QPen>
#include "ArrowItem.h"

ArrowItem::ArrowItem(Overlay& overlay, qreal x, qreal y)
    : LineItem(overlay, x, y),
      pathGraphicItem_(new PathGraphicItem(this)) {
    addGraphicItem(pathGraphicItem_);
}

void ArrowItem::setPen(const QPen& pen) {
    LineItem::setPen(pen);

    QPen pathPen = QPen(pen);
    pathPen.setWidth(1);

    pathGraphicItem_->setPen(pathPen);
    pathGraphicItem_->setBrush(QBrush(pen.brush()));
}
