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

    QGraphicsRectItem *rectTop;
    QGraphicsRectItem *rectBottom;
    QGraphicsRectItem *rectLeft;
    QGraphicsRectItem *rectRight;

    EditorForm* _form;
};

#endif // VISIBLEAREAMODE_H
