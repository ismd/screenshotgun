#pragma once

#include "AbstractItem.h"
#include "graphicitems/EllipseGraphicItem.h"

class EllipseItem : public AbstractItem {

public:
    EllipseItem(Overlay&, qreal x, qreal y);

    void setPen(const QPen& pen);

protected:
    EllipseGraphicItem* ellipseGraphicItem_;
};
