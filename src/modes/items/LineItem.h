#ifndef SCREENSHOTGUN_LINEITEM_H
#define SCREENSHOTGUN_LINEITEM_H

#include "AbstractItem.h"
#include "graphicitems/LineGraphicItem.h"

class LineItem : public AbstractItem {

public:
    LineItem(Overlay&, qreal x, qreal y);

    void setPen(const QPen& pen);

protected:
    LineGraphicItem* lineGraphicItem_;
};

#endif //SCREENSHOTGUN_LINEITEM_H
