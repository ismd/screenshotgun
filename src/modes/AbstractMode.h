#ifndef SCREENSHOTGUN_ABSTRACTMODE_H
#define SCREENSHOTGUN_ABSTRACTMODE_H

#include <QPen>

class Overlay;

class AbstractMode : public QObject {
    Q_OBJECT

public:
    AbstractMode(Overlay&);

    virtual void init(int x, int y) = 0;
    virtual void move(int x, int y) = 0;
    virtual void stop(int x, int y) = 0;

protected:
    Overlay& overlay_;
    QPen pen;
};

#endif // SCREENSHOTGUN_ABSTRACTMODE_H
