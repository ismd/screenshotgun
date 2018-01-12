#include <QBrush>
#include "EllipseItem.h"

EllipseItem::EllipseItem(Overlay& overlay, qreal x, qreal y)
    : AbstractItem(overlay),
      ellipseGraphicItem_(new EllipseGraphicItem(this, x, y)) {
    ellipseGraphicItem_->setBrush(Qt::NoBrush);
    addGraphicItem(ellipseGraphicItem_);
}

void EllipseItem::setPen(const QPen& pen) {
    ellipseGraphicItem_->setPen(pen);
}
