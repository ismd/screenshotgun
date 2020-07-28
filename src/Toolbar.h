#pragma once

#include "services/Server.h"
#include "ui_Toolbar.h"

#include <vector>
#include <QPushButton>
#include <QWidget>

class Overlay;

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
    explicit Toolbar(QWidget*, Overlay&);
    ~Toolbar();

    Overlay& overlay() const;
    void select(const ToolbarMode, bool animate = false);
    void setSelectedNext();
    void setSelectedPrevious();
    void show();
    void submit();
    QImage& image() const;

protected:
    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);

private slots:
    void on_visibleAreaButton_clicked();
    void on_lineButton_clicked();
    void on_arrowButton_clicked();
    void on_rectButton_clicked();
    void on_ellipseButton_clicked();
    void on_textButton_clicked();
    void on_okButton_clicked();

private:
    std::vector<QPushButton*>::const_iterator getSelected() const;
    void setSelected(QPushButton*, bool animate = true);

    Ui::Toolbar* ui;
    Overlay& overlay_;
    std::vector<QPushButton*> buttons_;
    QPushButton* selected_;
    bool dragging_;
    struct {
        int x;
        int y;
    } initDragCoords_;
    QPropertyAnimation animation_;
    QImage* image_;
};
