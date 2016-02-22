#ifndef SCREENSHOTGUN_ITEMFACTORY_H
#define SCREENSHOTGUN_ITEMFACTORY_H

#include "AbstractItem.h"
#include "../../Toolbar.h"

class ItemFactory {

public:
    ItemFactory();
    AbstractItem* createItem(ToolbarMode);

private:
    QPen pen_;
};

#endif //SCREENSHOTGUN_ITEMFACTORY_H
