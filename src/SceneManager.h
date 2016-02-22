#ifndef SCREENSHOTGUN_SCENEMANAGER_H
#define SCREENSHOTGUN_SCENEMANAGER_H

#include <QGraphicsItem>
#include "modes/LineMode.h"
#include "modes/ArrowMode.h"
#include "modes/EllipseMode.h"
#include "modes/RectMode.h"
#include "modes/TextMode.h"
#include "modes/VisibleAreaMode.h"
#include "Scene.h"
#include "Toolbar.h"

class AppView;

class SceneManager : public QObject {
    Q_OBJECT

public:
    SceneManager(AppView&);
    ~SceneManager();

    AppView& appView();
    Scene& scene();
    QGraphicsItem* getSelection();
    void reinitVisibleArea();

    void setMode(const ToolbarMode);
    AbstractMode* mode() const;

    VisibleAreaMode* visibleAreaMode();
    LineMode& lineMode();
    ArrowMode& arrowMode();
    RectMode& rectMode();
    EllipseMode& ellipseMode();
    TextMode& textMode();

signals:
    void modeChanged(ToolbarMode);

private slots:
    void selectItem();

private:
    AppView& appView_;
    Scene scene_;
    QGraphicsItem* selection_;

    AbstractMode* currentMode_;
    VisibleAreaMode* visibleAreaMode_;
    LineMode lineMode_;
    ArrowMode arrowMode_;
    RectMode rectMode_;
    EllipseMode ellipseMode_;
    TextMode textMode_;
};

#endif //SCREENSHOTGUN_SCENEMANAGER_H
