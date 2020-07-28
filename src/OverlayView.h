#pragma once

#include "modes/LineMode.h"
#include "modes/ArrowMode.h"
#include "modes/EllipseMode.h"
#include "modes/RectMode.h"
#include "modes/TextMode.h"
#include "modes/VisibleAreaMode.h"
#include "Toolbar.h"

#include <QGraphicsView>

class Overlay;

class OverlayView : public QGraphicsView {
    Q_OBJECT

public:
    explicit OverlayView(QWidget*, Overlay&);
    ~OverlayView();

    QGraphicsScene& scene();
    VisibleAreaMode& visibleAreaMode() const;
    void setMode(const ToolbarMode);
    void reinitVisibleArea();
    bool movingItem() const;
    void setMovingItem(bool);
    void setCursor(const QCursor&);

protected:
    void showEvent(QShowEvent*);
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void keyReleaseEvent(QKeyEvent*);
    void wheelEvent(QWheelEvent*);

private:
    Overlay& overlay_;
    QGraphicsScene scene_;

    VisibleAreaMode* visibleAreaMode_;
    LineMode lineMode_;
    ArrowMode arrowMode_;
    RectMode rectMode_;
    EllipseMode ellipseMode_;
    TextMode textMode_;

    AbstractMode* currentMode_;
    bool usingMode_;
    bool movingItem_;
};
