#pragma once

#include "AbstractItem.h"
#include "graphicitems/LineGraphicItem.h"

class LineItem : public AbstractItem {

public:
    LineItem(Overlay&, qreal x, qreal y);

    void setPen(const QPen& pen);
    void select();

protected:
    LineGraphicItem* lineGraphicItem_;
};
