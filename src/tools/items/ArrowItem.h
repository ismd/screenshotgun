#pragma once

#include "AbstractItem.h"
#include "LineItem.h"
#include "graphicitems/PathGraphicItem.h"

class ArrowItem : public LineItem {

public:
    ArrowItem(Overlay&, qreal x, qreal y);

    void setPen(const QPen& pen);

protected:
    PathGraphicItem* pathGraphicItem_;
};
