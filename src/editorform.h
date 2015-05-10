#ifndef EDITORFORM_H
#define EDITORFORM_H

#include <QPushButton>
#include <QWidget>
#include "modes/linemode.h"
#include "modes/rectmode.h"
#include "modes/visibleareamode.h"
#include "server.h"

class EditorView;

namespace Ui {
    class EditorForm;
}

class EditorForm : public QWidget
{
    Q_OBJECT

public:
    explicit EditorForm(EditorView*);
    ~EditorForm();
    AbstractMode* mode();
    EditorView* view();
    void setSelectedNext();
    void setSelectedPrevious();

    struct {
        VisibleAreaMode *visibleArea;
        LineMode *line;
        RectMode *rect;
    } modes;

protected:
    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);

private slots:
    void on_visibleAreaButton_clicked();
    void on_lineButton_clicked();
    void on_rectButton_clicked();
    void on_okButton_clicked();

private:
    void setSelected(QPushButton*);

    Ui::EditorForm *ui;
    EditorView* _editorView;
    AbstractMode* _mode;
    QLinkedList<QPushButton*> _buttons;
    QPushButton* _selected;
    bool _dragging;
    struct {
        int x;
        int y;
    } _initDragCoords;
};

#endif // EDITORFORM_H
