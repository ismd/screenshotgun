#ifndef EDITORFORM_H
#define EDITORFORM_H

#include <QWidget>

#include "modes/abstractmode.h"

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

private slots:
    void on_visibleAreaButton_clicked();
    void on_lineButton_clicked();

private:
    Ui::EditorForm *ui;
    QGraphicsScene *scene;
    AbstractMode *mode;
};

#endif // EDITORFORM_H
