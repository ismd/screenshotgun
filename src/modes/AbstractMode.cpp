#include "AbstractMode.h"

AbstractMode::AbstractMode(QGraphicsScene& scene) : scene_(scene) {
    pen.setColor(Qt::red);
    pen.setWidth(3);
}
