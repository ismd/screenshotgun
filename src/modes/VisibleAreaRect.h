#ifndef SCREENSHOTGUN_VISIBLEAREARECT_H
#define SCREENSHOTGUN_VISIBLEAREARECT_H

#include <QGraphicsObject>
#include <QGraphicsRectItem>

enum class ResizeDirection {
    TOP_LEFT,
    TOP,
    TOP_RIGHT,
    LEFT,
    RIGHT,
    BOTTOM_LEFT,
    BOTTOM,
    BOTTOM_RIGHT
};

class VisibleAreaMode;
class SceneManager;

class VisibleAreaRect : public QGraphicsRectItem {

public:
    VisibleAreaRect(VisibleAreaMode&, ResizeDirection);

signals:
    void resizeArea(int, int, int, int);

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent*);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent*);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent*);

private:
    void resize(QPointF, QPointF);
    VisibleAreaMode& visibleAreaMode_;
    ResizeDirection resizeDirection_;
    SceneManager& sceneManager_;
};

#endif //SCREENSHOTGUN_VISIBLEAREARECT_H
