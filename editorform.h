#ifndef EDITORFORM_H
#define EDITORFORM_H

#include <QWidget>

#include "modes/visibleareamode.h"

class EditorView;

namespace Ui {
class EditorForm;
}

class EditorForm : public QWidget
{
    Q_OBJECT

public:
    explicit EditorForm(QWidget *parent, QGraphicsScene*);
    ~EditorForm();
    AbstractMode* getMode();
    VisibleAreaMode* getVisibleArea();

private slots:
    void on_visibleAreaButton_clicked();
    void on_lineButton_clicked();

private:
    void newVisibleArea();
    Ui::EditorForm *ui;
    QGraphicsScene *scene;
    AbstractMode *mode;
    VisibleAreaMode *visibleArea;
};

#endif // EDITORFORM_H
