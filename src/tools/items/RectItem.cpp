#include "RectItem.h"

#include <QBrush>

RectItem::RectItem(Overlay& overlay, qreal x, qreal y)
    : AbstractItem(overlay),
      rectGraphicItem_(new RectGraphicItem(this, x, y)) {
    rectGraphicItem_->setBrush(Qt::NoBrush);
    addGraphicItem(rectGraphicItem_);
}

void RectItem::setPen(const QPen& pen) {
    rectGraphicItem_->setPen(pen);
}
