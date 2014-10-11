#include "editorform.h"
#include "ui_editorform.h"

EditorForm::EditorForm(QWidget *parent, AbstractMode* mode, VisibleArea* area) :
    QWidget(parent),
    ui(new Ui::EditorForm),
    mode(mode),
    visibleArea(area)
{
    ui->setupUi(this);
}

EditorForm::~EditorForm()
{
    delete ui;
}

void EditorForm::on_lineButton_clicked()
{
    mode = new LineMode(visibleArea);
}
