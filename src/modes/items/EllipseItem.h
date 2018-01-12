#ifndef SCREENSHOTGUN_ELLIPSEITEM_H
#define SCREENSHOTGUN_ELLIPSEITEM_H

#include "AbstractItem.h"
#include "graphicitems/EllipseGraphicItem.h"

class EllipseItem : public AbstractItem {

public:
    EllipseItem(Overlay&, qreal x, qreal y);

    void setPen(const QPen& pen);

protected:
    EllipseGraphicItem ellipseGraphicItem_;
};

#endif //SCREENSHOTGUN_ELLIPSEITEM_H
