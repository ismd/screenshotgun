#include "editorform.h"
#include "ui_editorform.h"
#include "modes/visibleareamode.h"
#include "modes/linemode.h"
#include "modes/rectmode.h"

EditorForm::EditorForm(QWidget *parent, QGraphicsScene *scene) :
    QWidget(parent),
    ui(new Ui::EditorForm),
    scene(scene),
    visibleArea(NULL)
{
    hide();
    ui->setupUi(this);

    // Setting default mode
    newVisibleArea();
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
    newVisibleArea();
}

void EditorForm::on_lineButton_clicked()
{
    mode = new LineMode(scene);
}

void EditorForm::on_rectButton_clicked()
{
    mode = new RectMode(scene);
}

void EditorForm::newVisibleArea()
{
    visibleArea = new VisibleAreaMode(scene, static_cast<EditorForm*>(this));
    mode = visibleArea;
}
