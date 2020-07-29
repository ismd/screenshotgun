#pragma once

#include "AbstractItem.h"
#include "graphicitems/RectGraphicItem.h"

class RectItem : public AbstractItem {

public:
    RectItem(Overlay&, qreal x, qreal y);

    void setPen(const QPen& pen);

protected:
    RectGraphicItem* rectGraphicItem_;
};
