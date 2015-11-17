#ifndef SCREENSHOTGUN_ELLIPSEMODE_H
#define SCREENSHOTGUN_ELLIPSEMODE_H

#include "AbstractMode.h"

class EllipseMode : public AbstractMode {

public:
    EllipseMode(QGraphicsScene&);

    void init(int x, int y);
    void move(int x, int y);
    void stop(int x, int y);

private:
    QGraphicsEllipseItem*ellipse_;

    struct {
        int x;
        int y;
    } coords;
};

#endif // SCREENSHOTGUN_ELLIPSEMODE_H
