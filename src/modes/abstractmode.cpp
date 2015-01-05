#include "../modes/abstractmode.h"

AbstractMode::AbstractMode(QGraphicsScene *scene) : _scene(scene)
{
    _pen = new QPen(Qt::red);
    _pen->setWidth(3);
}

AbstractMode::~AbstractMode()
{
    delete _pen;
}
