#include "editorform.h"
#include "ui_editorform.h"
#include "modes/visibleareamode.h"
#include "modes/linemode.h"

EditorForm::EditorForm(QWidget *parent, QGraphicsScene *scene) :
    QWidget(parent),
    ui(new Ui::EditorForm),
    scene(scene),
    visibleArea(NULL)
{
    hide();
    ui->setupUi(this);

    // Setting default mode
    setVisibleArea(new VisibleAreaMode(scene, static_cast<EditorForm*>(this)));
}

EditorForm::~EditorForm()
{
    delete ui;
    delete mode;
    delete visibleArea;
}

AbstractMode* EditorForm::getMode()
{
    return mode;
}

VisibleAreaMode* EditorForm::getVisibleArea()
{
    return visibleArea;
}

void EditorForm::on_visibleAreaButton_clicked()
{
    setVisibleArea(new VisibleAreaMode(scene, static_cast<EditorForm*>(this)));
}

void EditorForm::on_lineButton_clicked()
{
    mode = new LineMode(scene);
}

void EditorForm::setVisibleArea(VisibleAreaMode *area)
{
    visibleArea = area;
    mode = visibleArea;
}
