#include "../modes/abstractmode.h"

AbstractMode::AbstractMode(QGraphicsScene *scene) : scene(scene)
{
    _pen = new QPen(Qt::red);
    _pen->setWidth(5);
}

AbstractMode::~AbstractMode()
{
}
