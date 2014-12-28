#ifndef EDITORFORM_H
#define EDITORFORM_H

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

    struct {
        VisibleAreaMode *visibleArea;
        LineMode *line;
        RectMode *rect;
    } modes;

private slots:
    void on_visibleAreaButton_clicked();
    void on_lineButton_clicked();
    void on_rectButton_clicked();
    void on_okButton_clicked();

private:
    Ui::EditorForm *ui;
    EditorView* _editorView;
    AbstractMode* _mode;
};

#endif // EDITORFORM_H
