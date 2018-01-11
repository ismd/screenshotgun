#include "AbstractMode.h"

AbstractMode::AbstractMode(Overlay& overlay) : overlay_(overlay) {
    pen.setColor(Qt::red);
    pen.setWidth(3);
}
