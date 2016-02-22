#include "AbstractItem.h"

void AbstractItem::init(int x, int y) {
}

void AbstractItem::move(int x, int y) {
}

void AbstractItem::stop(int x, int y) {
    move(x, y);
}
