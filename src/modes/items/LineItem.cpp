#include <QCursor>
#include "LineItem.h"

LineItem::LineItem(Overlay& overlay, qreal x, qreal y)
    : AbstractItem(overlay),
      lineGraphicItem_(new LineGraphicItem(this, x, y)) {
    addGraphicItem(lineGraphicItem_);
}

void LineItem::setPen(const QPen& pen) {
    lineGraphicItem_->setPen(pen);
}

void LineItem::select() {
}
