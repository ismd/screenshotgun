#include <QApplication>
#include <QDesktopWidget>
#include <QPainter>
#include "../modes/visibleareamode.h"
#include "../editorform.h"
#include "../editorview.h"

VisibleAreaMode::VisibleAreaMode(QGraphicsScene *scene, EditorForm *form) :
    AbstractMode(scene),
    _form(form),
    _rectTop(new QGraphicsRectItem),
    _rectBottom(new QGraphicsRectItem),
    _rectLeft(new QGraphicsRectItem),
    _rectRight(new QGraphicsRectItem),
    _lineTop(new QGraphicsLineItem),
    _lineBottom(new QGraphicsLineItem),
    _lineLeft(new QGraphicsLineItem),
    _lineRight(new QGraphicsLineItem)
{
    QPen pen(Qt::NoPen);
    QBrush brush(Qt::black);

    _rectTop->setOpacity(.65);
    _rectBottom->setOpacity(.65);
    _rectLeft->setOpacity(.65);
    _rectRight->setOpacity(.65);

    _rectTop->setPen(pen);
    _rectBottom->setPen(pen);
    _rectLeft->setPen(pen);
    _rectRight->setPen(pen);

    _rectTop->setBrush(brush);
    _rectBottom->setBrush(brush);
    _rectLeft->setBrush(brush);
    _rectRight->setBrush(brush);

    _rectTop->setZValue(1);
    _rectBottom->setZValue(1);
    _rectLeft->setZValue(1);
    _rectRight->setZValue(1);

    // First rectangle fullscreen
    _rectTop->setRect(0, 0, _scene->width(), _scene->height());

    _scene->addItem(_rectTop);
    _scene->addItem(_rectBottom);
    _scene->addItem(_rectLeft);
    _scene->addItem(_rectRight);

    QPen linePen;
    linePen.setWidthF(.2);
    linePen.setColor(QColor(230, 230, 230));

    _lineTop->setPen(linePen);
    _lineBottom->setPen(linePen);
    _lineLeft->setPen(linePen);
    _lineRight->setPen(linePen);

    _lineTop->setZValue(1);
    _lineBottom->setZValue(1);
    _lineLeft->setZValue(1);
    _lineRight->setZValue(1);

    _scene->addItem(_lineTop);
    _scene->addItem(_lineBottom);
    _scene->addItem(_lineLeft);
    _scene->addItem(_lineRight);
}

VisibleAreaMode::~VisibleAreaMode()
{
    delete _rectTop;
    delete _rectBottom;
    delete _rectLeft;
    delete _rectRight;
    delete _lineTop;
    delete _lineBottom;
    delete _lineLeft;
    delete _lineRight;
}

void VisibleAreaMode::init(int x, int y)
{
    _initialized = true;
    _form->hide();

    area.x = x;
    area.y = y;
    area.width = 0;
    area.height = 0;

    set(x, y, 0, 0);
}

void VisibleAreaMode::move(int x, int y)
{
    if (!_initialized) {
        area.x = x;
        area.y = y;
        area.width = 0;
        area.height = 0;
        set(area.x, area.y, area.width, area.height);
    }

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
    _form->view()->setMouseTracking(false);

    move(x, y);
    const int padding = 10;

    QDesktopWidget *desktop = QApplication::desktop();
    QRect geo = desktop->screenGeometry(desktop->screenNumber(QCursor::pos()));

    // Width
    int formX = area.x + area.width + 28;
    int screenWidth = geo.width();
    int formWidth = _form->width();

    if (formX + formWidth + padding > screenWidth) {
        formX = screenWidth - formWidth - padding;
    }

    // Height
    int formHeight = _form->height();
    int formY = area.y + area.height / 2 - formHeight / 2;
    int screenHeight = geo.height();

    if (formY < padding) {
        formY = padding;
    } else if (formY + formHeight + padding > screenHeight) {
        formY = screenHeight - formHeight - padding;
    }

    _form->setGeometry(formX, formY, formWidth, formHeight);
    _form->show();
}

void VisibleAreaMode::set(int x, int y, int width, int height)
{
    int sceneWidth = _scene->width(),
        sceneHeight = _scene->height();

    _rectTop->setRect(0, 0, sceneWidth, y);
    _rectBottom->setRect(0, y + height, sceneWidth, sceneHeight - y - height);
    _rectLeft->setRect(0, y, x, height);
    _rectRight->setRect(x + width, y, sceneWidth - x - width, height);

    QDesktopWidget *desktop = QApplication::desktop();
    QRect geo = desktop->screenGeometry(desktop->screenNumber(QCursor::pos()));

    int screenWidth = geo.width();
    int screenHeight = geo.height();

    // Horizontal and vertical lines
    if (0 == width && 0 == height) {
        _lineTop->setLine(0, y, screenWidth, y);
        _lineLeft->setLine(x, 0, x, screenHeight);
        return;
    }

    _lineTop->setLine(0, y - 1, screenWidth, y - 1);
    _lineBottom->setLine(0, y + height + 1, screenWidth, y + height + 1);
    _lineLeft->setLine(x - 1, 0, x - 1, screenHeight);
    _lineRight->setLine(x + width + 1, 0, x + width + 1, sceneHeight);
}

bool VisibleAreaMode::initialized()
{
    return _initialized;
}
