#ifndef SCREENSHOTGUN_TEXTITEM_H
#define SCREENSHOTGUN_TEXTITEM_H

#include <QPlainTextEdit>
#include "AbstractItem.h"

class TextItem : public AbstractItem, public QPlainTextEdit {

public:
    virtual QGraphicsItem* graphicsItem();
    virtual void updatePen(const QPen& pen);
};

#endif //SCREENSHOTGUN_TEXTITEM_H
