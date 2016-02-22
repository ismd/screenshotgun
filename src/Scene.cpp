#include <QGraphicsSceneMouseEvent>
#include "App.h"
#include "AppView.h"
#include "Scene.h"
#include "SceneManager.h"

Scene::Scene(SceneManager& sceneManager)
    : sceneManager_(sceneManager),
      usingMode_(false) {
    connect(&sceneManager_, SIGNAL(modeChanged(ToolbarMode)),
            this, SLOT(setMode(ToolbarMode)));
}

SceneManager& Scene::sceneManager() const {
    return sceneManager_;
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent* e) {
    QGraphicsScene::mousePressEvent(e);

    if (e->isAccepted()) {
        return;
    }

    QPointF pos = e->scenePos();
    int x = pos.x();
    int y = pos.y();

    usingMode_ = true;
    mode_->init(x, y);
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent* e) {
    QGraphicsScene::mouseMoveEvent(e);

    if (e->isAccepted()) {
        return;
    }

    VisibleAreaMode* visibleAreaMode = sceneManager_.visibleAreaMode();

    if (usingMode_ || mode_ == visibleAreaMode && !visibleAreaMode->initialized()) {
        QPointF pos = e->scenePos();
        int x = pos.x();
        int y = pos.y();

        mode_->move(x, y);
    }
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent* e) {
    QGraphicsScene::mouseReleaseEvent(e);

    if (e->isAccepted()) {
        return;
    }

    QPointF pos = e->scenePos();
    int x = pos.x();
    int y = pos.y();

    VisibleAreaMode* visibleAreaMode = sceneManager_.visibleAreaMode();

    mode_->stop(x, y);

    if (mode_ != visibleAreaMode) {
        usingMode_ = false;
    }
}

void Scene::wheelEvent(QGraphicsSceneWheelEvent* e) {
    if (e->delta() < 0) {
        sceneManager_.appView().toolbar().setSelectedNext();
    } else {
        sceneManager_.appView().toolbar().setSelectedPrevious();
    }
}

void Scene::keyReleaseEvent(QKeyEvent* e) {
    int key = e->key();
    AppView& appView = sceneManager_.appView();

    if (key == Qt::Key_Escape) {
        appView.hide();
        appView.toolbar().hide();
    } else if (key == Qt::Key_Return) {
        TextMode& textMode = sceneManager_.textMode();

        if (sceneManager_.mode() != &textMode || textMode.textArea() == 0 || !textMode.textArea()->hasFocus()) {
            appView.app().setCopyImageToClipboard(e->modifiers().testFlag(Qt::AltModifier));
            appView.toolbar().submit();
        }
    }

    QGraphicsScene::keyReleaseEvent(e);
}

void Scene::setMode(const ToolbarMode mode) {
    switch (mode) {
        case ToolbarMode::VISIBLE_AREA:
            mode_ = sceneManager_.visibleAreaMode();
            break;

        case ToolbarMode::LINE:
            mode_ = &sceneManager_.lineMode();
            break;

        case ToolbarMode::ARROW:
            mode_ = &sceneManager_.arrowMode();
            break;

        case ToolbarMode::RECT:
            mode_ = &sceneManager_.rectMode();
            break;

        case ToolbarMode::ELLIPSE:
            mode_ = &sceneManager_.ellipseMode();
            break;

        case ToolbarMode::TEXT:
            mode_ = &sceneManager_.textMode();
            break;
    }
}
