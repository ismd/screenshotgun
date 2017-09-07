#ifndef SCREENSHOTGUN_OVERLAY_H
#define SCREENSHOTGUN_OVERLAY_H

#include <QGraphicsView>
#include <QMouseEvent>
#include "modes/LineMode.h"
#include "modes/ArrowMode.h"
#include "modes/EllipseMode.h"
#include "modes/RectMode.h"
#include "modes/TextMode.h"
#include "modes/VisibleAreaMode.h"
#include "Toolbar.h"

#if defined(Q_OS_LINUX)
    #include "qxt/qxtglobalshortcut.h"
#elif defined(Q_OS_WIN32)
    #include <windows.h>
#endif

class App;

class Overlay : public QGraphicsView {
    Q_OBJECT

public:
    explicit Overlay(App&);
    ~Overlay();

    App& app() const;
    QGraphicsScene& scene();
    VisibleAreaMode& visibleAreaMode() const;
    void setMode(const ToolbarMode);
    void reinitVisibleArea();
    Toolbar& toolbar();

signals:
    void toolChanged(ToolbarMode);

public slots:
    void makeScreenshot();

protected:
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void wheelEvent(QWheelEvent*);
    void keyReleaseEvent(QKeyEvent*);

private:
    App& app_;
    QGraphicsScene scene_;
    Toolbar toolbar_;
    QPixmap screenshot_;

    AbstractMode* currentMode_;
    VisibleAreaMode* visibleAreaMode_;
    LineMode lineMode_;
    ArrowMode arrowMode_;
    RectMode rectMode_;
    EllipseMode ellipseMode_;
    TextMode textMode_;
    bool usingMode_;
};

#endif //SCREENSHOTGUN_OVERLAY_H
