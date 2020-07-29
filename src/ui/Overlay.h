#pragma once

#include "src/ui/OverlayView.h"
#include "src/ui/Toolbar.h"

// #if defined(Q_OS_LINUX)
// #include "qxt/qxtglobalshortcut.h"
// #elif defined(Q_OS_WIN32)
// #include <windows.h>
// #endif

class Overlay : public QWidget {
    Q_OBJECT

public:
    explicit Overlay();

    // QGraphicsScene& scene();
    // VisibleAreaMode& visibleAreaMode() const;
    // void setMode(const ToolbarMode);
    // void reinitVisibleArea();
    // void setCursor(const QCursor&);
    // void setCursorLocked(bool);
    // void addItem(AbstractItem*);

    OverlayView overlayView;
    Toolbar toolbar;

// protected:
//     void hideEvent(QHideEvent*);

// private:
//     QPixmap screenshot_;
//     bool cursorLocked_;
//     QVector<AbstractItem*> items_;
};
