#ifndef SCREENSHOTGUN_SCENE_H
#define SCREENSHOTGUN_SCENE_H

#include <QGraphicsScene>
#include "Toolbar.h"

class AbstractMode;
class SceneManager;

class Scene : public QGraphicsScene {
    Q_OBJECT

public:
    Scene(SceneManager&);
    SceneManager& sceneManager() const;

public slots:
    void setMode(const ToolbarMode);

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent*);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent*);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent*);
    virtual void wheelEvent(QGraphicsSceneWheelEvent*);
    virtual void keyReleaseEvent(QKeyEvent*);

private:
    SceneManager& sceneManager_;
    AbstractMode* mode_;
    bool usingMode_;
};

#endif //SCREENSHOTGUN_SCENE_H
