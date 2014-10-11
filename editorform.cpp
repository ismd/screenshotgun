#include "editorform.h"
#include "ui_editorform.h"

EditorForm::EditorForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditorForm)
{
    ui->setupUi(this);
}

EditorForm::~EditorForm()
{
    delete ui;
}

void EditorForm::on_lineButton_clicked()
{

}
