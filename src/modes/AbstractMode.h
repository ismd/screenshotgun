#ifndef SCREENSHOTGUN_ABSTRACTMODE_H
#define SCREENSHOTGUN_ABSTRACTMODE_H

#include "items/ItemFactory.h"
#include "../Scene.h"

class AbstractMode : public QObject {
    Q_OBJECT

public:
    AbstractMode(Scene&);
    Scene& scene();

    virtual void init(int x, int y);
    virtual void move(int x, int y);
    virtual void stop(int x, int y);

protected:
    Scene& scene_;
    static ItemFactory itemFactory_;
    AbstractItem* item_;
};

#endif // SCREENSHOTGUN_ABSTRACTMODE_H
