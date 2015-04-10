#include "editorform.h"
#include "ui_editorform.h"
#include "editorview.h"

EditorForm::EditorForm(EditorView *parent) :
    QWidget(parent),
    ui(new Ui::EditorForm),
    _editorView(parent)
{
    hide();
    ui->setupUi(this);
    ui->selectedCircle->lower();

    QGraphicsScene *scene = _editorView->scene();

    // Setting default mode
    modes.visibleArea = new VisibleAreaMode(scene, static_cast<EditorForm*>(this));
    modes.line = new LineMode(scene);
    modes.rect = new RectMode(scene);

    _mode = modes.visibleArea;
    _editorView->setMouseTracking(true);

    setSelected(ui->visibleAreaButton);
    _buttons.append(ui->rectButton);
    _buttons.append(ui->visibleAreaButton);
    _buttons.append(ui->lineButton);
}

EditorForm::~EditorForm()
{
    delete modes.visibleArea;
    delete modes.line;
    delete modes.rect;
}

AbstractMode* EditorForm::mode()
{
    return _mode;
}

EditorView* EditorForm::view()
{
    return _editorView;
}

void EditorForm::on_visibleAreaButton_clicked()
{
    setSelected(ui->visibleAreaButton);
    _editorView->setMouseTracking(!modes.visibleArea->initialized());
}

void EditorForm::on_lineButton_clicked()
{
    setSelected(ui->lineButton);
    _editorView->setMouseTracking(false);
}

void EditorForm::on_rectButton_clicked()
{
    setSelected(ui->rectButton);
    _editorView->setMouseTracking(false);
}

void EditorForm::on_okButton_clicked()
{
    _editorView->hide();
    hide();

    QGraphicsScene *scene = _editorView->scene();

    scene->clearSelection();
    scene->setSceneRect(modes.visibleArea->area.x,
                        modes.visibleArea->area.y,
                        modes.visibleArea->area.width,
                        modes.visibleArea->area.height);

    QImage image(scene->sceneRect().size().toSize(), QImage::Format_ARGB32);
    image.fill(Qt::transparent);

    QPainter painter(&image);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    scene->render(&painter);

    QByteArray bytes;
    QBuffer buffer(&bytes);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG");

    _editorView->server()->upload(bytes);
}

void EditorForm::setSelectedNext()
{
    QLinkedListIterator<QPushButton*> i(_buttons);

    while (i.next() != _selected) {
    }

    if (!i.hasNext()) {
        //setSelected(_buttons.front());
        return;
    }

    setSelected(i.next());
}

void EditorForm::setSelectedPrevious()
{
    QLinkedListIterator<QPushButton*> i(_buttons);

    while (i.next() != _selected) {
    }

    i.previous();

    if (!i.hasPrevious()) {
        //setSelected(_buttons.back());
        return;
    }

    setSelected(i.previous());
}

void EditorForm::setSelected(QPushButton *button)
{
    _selected = button;

    if (button == ui->visibleAreaButton) {
        _mode = modes.visibleArea;
    } else if (button == ui->lineButton) {
        _mode = modes.line;
    } else if (button == ui->rectButton) {
        _mode = modes.rect;
    }

    int x = ui->selectedCircle->x();
    int y = ui->selectedCircle->y();
    int width = ui->selectedCircle->width();
    int height = ui->selectedCircle->height();

    QPropertyAnimation *animation = new QPropertyAnimation(ui->selectedCircle, "geometry");
    animation->setDuration(500);
    animation->setStartValue(QRect(x, y, width, height));
    animation->setEndValue(QRect(x, button->y(), width, height));

    animation->start();
}
