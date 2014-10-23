#include "editorform.h"
#include "ui_editorform.h"
#include "modes/visibleareamode.h"
#include "modes/linemode.h"

EditorForm::EditorForm(QWidget *parent, QGraphicsScene *scene) :
    QWidget(parent),
    ui(new Ui::EditorForm),
    scene(scene)
{
    hide();
    ui->setupUi(this);

    // Setting default mode
    mode = new VisibleAreaMode(scene, this);
}

EditorForm::~EditorForm()
{
    delete ui;
}

AbstractMode* EditorForm::getMode()
{
    return mode;
}

void EditorForm::on_visibleAreaButton_clicked()
{
    mode = new VisibleAreaMode(scene, this);
}

void EditorForm::on_lineButton_clicked()
{
    mode = new LineMode(scene);
}
