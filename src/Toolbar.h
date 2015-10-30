#ifndef SCREENSHOTGUN_TOOLBAR_H
#define SCREENSHOTGUN_TOOLBAR_H

#include <QPushButton>
#include <QWidget>
#include "Server.h"

class AppView;

enum class ToolbarMode {
    VISIBLE_AREA,
    LINE,
    ARROW,
    RECT
};

namespace Ui {
    class Toolbar;
}

class Toolbar : public QWidget {
    Q_OBJECT

public:
    explicit Toolbar(AppView&);
    ~Toolbar();

    AppView& appView();

    void select(ToolbarMode);
    void setSelectedNext();
    void setSelectedPrevious();

protected:
    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);

private slots:
    void on_visibleAreaButton_clicked();
    void on_lineButton_clicked();
    void on_arrowButton_clicked();
    void on_rectButton_clicked();
    void on_okButton_clicked();

private:
    void setSelected(QPushButton*);

    Ui::Toolbar* ui;
    AppView& appView_;
    QLinkedList<QPushButton*> buttons_;
    QPushButton* selected_;
    bool dragging_;
    struct {
        int x;
        int y;
    } initDragCoords_;
};

#endif // SCREENSHOTGUN_TOOLBAR_H
