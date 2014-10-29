#include "../modes/visibleareamode.h"
#include "../editorform.h"

VisibleAreaMode::VisibleAreaMode(QGraphicsScene *scene, EditorForm *form)
    : AbstractMode(scene), _form(form)
{
    QPen pen(Qt::NoPen);
    QBrush brush(Qt::black);

    // Black background (top, bottom, left, right)
    rectTop    = new QGraphicsRectItem;
    rectBottom = new QGraphicsRectItem;
    rectLeft   = new QGraphicsRectItem;
    rectRight  = new QGraphicsRectItem;

    rectTop->setOpacity(.65);
    rectBottom->setOpacity(.65);
    rectLeft->setOpacity(.65);
    rectRight->setOpacity(.65);

    rectTop->setPen(pen);
    rectBottom->setPen(pen);
    rectLeft->setPen(pen);
    rectRight->setPen(pen);

    rectTop->setBrush(brush);
    rectBottom->setBrush(brush);
    rectLeft->setBrush(brush);
    rectRight->setBrush(brush);

    rectTop->setZValue(1);
    rectBottom->setZValue(1);
    rectLeft->setZValue(1);
    rectRight->setZValue(1);

    // First rectangle fullscreen
    rectTop->setRect(0, 0, _scene->width(), _scene->height());

    _scene->addItem(rectTop);
    _scene->addItem(rectBottom);
    _scene->addItem(rectLeft);
    _scene->addItem(rectRight);
}

void VisibleAreaMode::init(int x, int y)
{
    _form->hide();

    area.x = x;
    area.y = y;
    area.width = 0;
    area.height = 0;

    set(x, y, 0, 0);
}

void VisibleAreaMode::move(int x, int y)
{
    if (x > area.x && qAbs(area.x + area.width - x) <= qAbs(area.x - x)) {
        area.width = x - area.x;
    } else {
        area.width = area.width + area.x - x;
        area.x = x;
    }

    if (y > area.y && qAbs(area.y + area.height - y) <= qAbs(area.y - y)) {
        area.height = y - area.y;
    } else {
        area.height = area.height + area.y - y;
        area.y = y;
    }

    set(area.x, area.y, area.width, area.height);
}

void VisibleAreaMode::stop(int x, int y)
{
    _form->setGeometry(area.x, area.y + area.height + 5, _form->width(), _form->height());
    _form->show();
}

void VisibleAreaMode::set(int x, int y, int width, int height)
{
    int sceneWidth = _scene->width(),
        sceneHeight = _scene->height();

    rectTop->setRect(0, 0, sceneWidth, y);
    rectBottom->setRect(0, y + height, sceneWidth, sceneHeight - y - height);
    rectLeft->setRect(0, y, x, height);
    rectRight->setRect(x + width, y, sceneWidth - x - width, height);
}
