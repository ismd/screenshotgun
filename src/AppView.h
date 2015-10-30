#ifndef SCREENSHOTGUN_APPVIEW_H
#define SCREENSHOTGUN_APPVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include "modes/LineMode.h"
#include "modes/ArrowMode.h"
#include "modes/RectMode.h"
#include "modes/VisibleAreaMode.h"
#include "Toolbar.h"

class App;

class AppView : public QGraphicsView {
    Q_OBJECT

public:
    explicit AppView(App&);
    ~AppView();

    App& app();
    void makeScreenshot();
    QGraphicsScene& scene();
    VisibleAreaMode& visibleAreaMode();
    void mode(ToolbarMode);
    void reinitVisibleArea();

#ifdef Q_OS_WIN32
    bool nativeEvent(const QByteArray & eventType, void * message, long *result);
#endif

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
};

#endif //SCREENSHOTGUN_APPVIEW_H
