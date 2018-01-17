#ifndef SCREENSHOTGUN_OVERLAY_H
#define SCREENSHOTGUN_OVERLAY_H

#include "OverlayView.h"
#include "Toolbar.h"

#if defined(Q_OS_LINUX)
    #include "qxt/qxtglobalshortcut.h"
#elif defined(Q_OS_WIN32)
    #include <windows.h>
#endif

class App;

class Overlay : public QWidget {
    Q_OBJECT

public:
    explicit Overlay(App&);

    App& app() const;
    OverlayView& overlayView();
    QGraphicsScene& scene();
    VisibleAreaMode& visibleAreaMode() const;
    void setMode(const ToolbarMode);
    void reinitVisibleArea();
    Toolbar& toolbar();
    void setCursor(const QCursor&);
    void setCursorLocked(bool);
    void addItem(AbstractItem*);

signals:
    void toolChanged(ToolbarMode);

public slots:
    void makeScreenshot();

protected:
    void hideEvent(QHideEvent*);

private:
    App& app_;
    OverlayView overlayView_;
    Toolbar toolbar_;
    QPixmap screenshot_;
    bool cursorLocked_;
    QVector<AbstractItem*> items_;
};

#endif //SCREENSHOTGUN_OVERLAY_H
