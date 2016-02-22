#ifndef SCREENSHOTGUN_VISIBLEAREAMODE_H
#define SCREENSHOTGUN_VISIBLEAREAMODE_H

#include <QGraphicsRectItem>
#include "AbstractMode.h"
#include "VisibleAreaRect.h"

class VisibleAreaMode : public AbstractMode {
    Q_OBJECT

public:
    VisibleAreaMode(Scene&, Toolbar&, int, int);

    virtual void init(int, int);
    virtual void move(int, int);
    virtual void stop(int, int);

    bool initialized();
    void resizeArea(int, int, int, int);
    Toolbar& toolbar();
    void updateToolbarPosition();

    struct {
        int x;
        int y;
        int width;
        int height;
    } area;

private slots:
    void modeChanged(ToolbarMode);

private:
    void updateSize();
    void setArea(int x, int y, int width, int height);
    void prepareRect(QGraphicsRectItem&);
    void prepareLine(QGraphicsLineItem&);

    QGraphicsRectItem activeRect_;
    QGraphicsRectItem* fullscreenRect_;

    VisibleAreaRect rectTopLeft_;
    VisibleAreaRect rectTop_;
    VisibleAreaRect rectTopRight_;
    VisibleAreaRect rectLeft_;
    VisibleAreaRect rectRight_;
    VisibleAreaRect rectBottomLeft_;
    VisibleAreaRect rectBottom_;
    VisibleAreaRect rectBottomRight_;

    QGraphicsLineItem lineTopLeft1_;
    QGraphicsLineItem lineTopLeft2_;
    QGraphicsLineItem lineTopRight1_;
    QGraphicsLineItem lineTopRight2_;
    QGraphicsLineItem lineBottomLeft1_;
    QGraphicsLineItem lineBottomLeft2_;
    QGraphicsLineItem lineBottomRight1_;
    QGraphicsLineItem lineBottomRight2_;

    Toolbar& toolbar_;
    bool initialized_;

    int maxWidth_;
    int maxHeight_;
};

#endif // SCREENSHOTGUN_VISIBLEAREAMODE_H
