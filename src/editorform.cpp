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

    QGraphicsScene *scene = _editorView->scene();

    // Setting default mode
    modes.visibleArea = new VisibleAreaMode(scene, static_cast<EditorForm*>(this));
    modes.line = new LineMode(scene);
    modes.rect = new RectMode(scene);

    _mode = modes.visibleArea;
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

void EditorForm::on_visibleAreaButton_clicked()
{
    _mode = modes.visibleArea;
}

void EditorForm::on_lineButton_clicked()
{
    _mode = modes.line;
}

void EditorForm::on_rectButton_clicked()
{
    _mode = modes.rect;
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
