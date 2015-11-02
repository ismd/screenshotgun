#ifndef SCREENSHOTGUN_APPVIEW_H
#define SCREENSHOTGUN_APPVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include "modes/LineMode.h"
#include "modes/ArrowMode.h"
#include "modes/RectMode.h"
#include "modes/VisibleAreaMode.h"
#include "Toolbar.h"

#if defined(Q_OS_LINUX)
    #include "qxt/qxtglobalshortcut.h"
#elif defined(Q_OS_WIN32)
    #include <windows.h>
#endif

class App;

class AppView : public QGraphicsView {
    Q_OBJECT

public:
    explicit AppView(App&);
    ~AppView();

    App& app();
    QGraphicsScene& scene();
    VisibleAreaMode& visibleAreaMode();
    void mode(ToolbarMode);
    void reinitVisibleArea();
    void initShortcut();

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

#if defined(Q_OS_LINUX)
    QxtGlobalShortcut shortcut_;
#elif defined(Q_OS_WIN32)
    bool nativeEvent(const QByteArray& eventType, void* message, long* result);
#endif
};

#endif //SCREENSHOTGUN_APPVIEW_H
