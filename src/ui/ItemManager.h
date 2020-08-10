#pragma once

#include "src/items/VisibleAreaItem.h"
#include "src/ui/Toolbar.h"

#include <QObject>

class ItemManager : public QObject {
    Q_OBJECT

public:
    ItemManager();

    /**
     * Pointer events
     */
    void init(QMouseEvent*);
    void move(QMouseEvent*);
    void stop(QMouseEvent*);

    VisibleAreaItem visibleAreaItem;

signals:
    void inited(ToolbarMode);
    void stopped(ToolbarMode);

private:
    QSet<AbstractItem*> items_;
    AbstractItem* current_;
};
