#pragma once

#include "ui_Toolbar.h"

#include <QPropertyAnimation>
#include <QPushButton>
#include <QWidget>
#include <vector>

enum class ToolbarMode {
    VISIBLE_AREA,
    LINE,
    ARROW,
    RECT,
    ELLIPSE,
    TEXT
};

class Toolbar : public QWidget {
    Q_OBJECT

public:
    explicit Toolbar();

    void select(const ToolbarMode);
    void select(const ToolbarMode, bool withAnimation);

    void selectNext();
    void selectPrevious();

signals:
    void screenshotButtonClicked();
    void toolChanged(const ToolbarMode);

protected:
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);

private slots:
    void on_visibleAreaButton_clicked();
    void on_lineButton_clicked();
    void on_arrowButton_clicked();
    void on_rectButton_clicked();
    void on_ellipseButton_clicked();
    void on_textButton_clicked();
    void on_okButton_clicked();

private:
    const std::vector<QPushButton*>::const_iterator getSelected() const;
    void setSelectedButton(QPushButton*, bool animate = true);

    Ui::Toolbar ui;
    std::vector<QPushButton*> buttons_;
    QPushButton* selected_;
    bool dragging_;
    struct {
        int x;
        int y;
    } initDragCoords_;
    QPropertyAnimation animation_;
};
