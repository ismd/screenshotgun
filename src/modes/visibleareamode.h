#ifndef VISIBLEAREAMODE_H
#define VISIBLEAREAMODE_H

#include <QWidget>
#include <QGraphicsRectItem>
#include "abstractmode.h"

class EditorForm;

class VisibleAreaMode : public AbstractMode
{
public:
    VisibleAreaMode(QGraphicsScene*, EditorForm*);
    virtual ~VisibleAreaMode();
    void init(int x, int y);
    void move(int x, int y);
    void stop(int x, int y);

    struct {
        int x;
        int y;
        int width;
        int height;
    } area;

private:
    void set(int x, int y, int width, int height);

    QGraphicsRectItem* _rectTop;
    QGraphicsRectItem* _rectBottom;
    QGraphicsRectItem* _rectLeft;
    QGraphicsRectItem* _rectRight;

    QGraphicsLineItem* _lineTop;
    QGraphicsLineItem* _lineBottom;
    QGraphicsLineItem* _lineLeft;
    QGraphicsLineItem* _lineRight;

    EditorForm* _form;
};

#endif // VISIBLEAREAMODE_H
