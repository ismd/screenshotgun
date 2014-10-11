#ifndef EDITORFORM_H
#define EDITORFORM_H

#include <QWidget>

#include "modes/abstractmode.h"
#include "modes/linemode.h"
#include "visiblearea.h"

class EditorView;

namespace Ui {
class EditorForm;
}

class EditorForm : public QWidget
{
    Q_OBJECT

public:
    explicit EditorForm(QWidget *parent = 0, AbstractMode* mode = NULL, VisibleArea* area = NULL);
    ~EditorForm();

private slots:
    void on_lineButton_clicked();

private:
    Ui::EditorForm *ui;
    AbstractMode *mode;
    VisibleArea *visibleArea;
};

#endif // EDITORFORM_H
