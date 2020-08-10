#pragma once

#include <QGraphicsView>

class OverlayView : public QGraphicsView {
    Q_OBJECT

public:
    explicit OverlayView();

    void show();
    void hide();

    QGraphicsScene scene;

signals:
    void enterClicked();
    void escapeClicked();

    void shown();
    void hided();

protected:
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void keyReleaseEvent(QKeyEvent*);
    void wheelEvent(QWheelEvent*);

private:
    bool movingItem_;
};
