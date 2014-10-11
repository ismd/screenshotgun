#ifndef EDITORFORM_H
#define EDITORFORM_H

#include <QWidget>

namespace Ui {
class EditorForm;
}

class EditorForm : public QWidget
{
    Q_OBJECT

public:
    explicit EditorForm(QWidget *parent = 0);
    ~EditorForm();

private slots:
    void on_lineButton_clicked();

private:
    Ui::EditorForm *ui;
};

#endif // EDITORFORM_H
