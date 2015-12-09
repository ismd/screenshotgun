#include <QGraphicsScene>
#include "App.h"
#include "Toolbar.h"

Toolbar::Toolbar(AppView& appView)
    : QWidget(&appView),
      ui(new Ui::Toolbar),
      appView_(appView),
      dragging_(false),
      image_(0) {

    hide();
    ui->setupUi(this);
    ui->selectedCircle->lower();
    setFocusPolicy(Qt::ClickFocus);

    buttons_.append(ui->visibleAreaButton);
    buttons_.append(ui->ellipseButton);
    buttons_.append(ui->rectButton);
    buttons_.append(ui->lineButton);
    buttons_.append(ui->arrowButton);
    buttons_.append(ui->textButton);

    animation_.setTargetObject(ui->selectedCircle);
    animation_.setPropertyName("geometry");
    setSelected(ui->visibleAreaButton);
}

Toolbar::~Toolbar() {
    delete ui;
    delete image_;
}

AppView& Toolbar::appView() const {
    return appView_;
}

void Toolbar::select(const ToolbarMode mode, bool animate) {
    switch (mode) {
        case ToolbarMode::VISIBLE_AREA:
            setSelected(ui->visibleAreaButton, animate);
            break;

        case ToolbarMode::LINE:
            setSelected(ui->lineButton, animate);
            break;

        case ToolbarMode::ARROW:
            setSelected(ui->arrowButton, animate);
            break;

        case ToolbarMode::RECT:
            setSelected(ui->rectButton, animate);
            break;

        case ToolbarMode::ELLIPSE:
            setSelected(ui->ellipseButton, animate);
            break;

        case ToolbarMode::TEXT:
            setSelected(ui->textButton, animate);
            break;
    }
}

void Toolbar::setSelectedNext() {
    QLinkedListIterator<QPushButton*> i(buttons_);

    while (i.next() != selected_) {
    }

    if (!i.hasNext()) {
        //setSelected(buttons_.front());
        return;
    }

    setSelected(i.next());
}

void Toolbar::setSelectedPrevious() {
    QLinkedListIterator<QPushButton*> i(buttons_);

    while (i.next() != selected_) {
    }

    i.previous();

    if (!i.hasPrevious()) {
        //setSelected(buttons_.back());
        return;
    }

    setSelected(i.previous());
}

void Toolbar::mousePressEvent(QMouseEvent* event) {
    const QRect dragLabelGeometry = ui->dragLabel->geometry();

    int x = event->x(),
        y = event->y(),
        dragLabelX = dragLabelGeometry.x(),
        dragLabelY = dragLabelGeometry.y();

    if (x < dragLabelX ||
        x > dragLabelX + dragLabelGeometry.width() ||
        y < dragLabelY ||
        y > dragLabelY + dragLabelGeometry.height())
    {
        return;
    }

    initDragCoords_.x = x;
    initDragCoords_.y = y;
    dragging_ = true;
}

void Toolbar::mouseReleaseEvent(QMouseEvent* event) {
    dragging_ = false;
}

void Toolbar::mouseMoveEvent(QMouseEvent* event) {
    if (!dragging_) {
        return;
    }

    move(geometry().x() + event->x() - initDragCoords_.x,
         geometry().y() + event->y() - initDragCoords_.y);
}

void Toolbar::on_visibleAreaButton_clicked() {
    setSelected(ui->visibleAreaButton);
}

void Toolbar::on_lineButton_clicked() {
    setSelected(ui->lineButton);
}

void Toolbar::on_arrowButton_clicked() {
    setSelected(ui->arrowButton);
}

void Toolbar::on_rectButton_clicked() {
    setSelected(ui->rectButton);
}

void Toolbar::on_ellipseButton_clicked() {
    setSelected(ui->ellipseButton);
}

void Toolbar::on_textButton_clicked() {
    setSelected(ui->textButton);
}

void Toolbar::on_okButton_clicked() {
    submit();
}

void Toolbar::show() {
    select(appView_.app().history().tool());
    QWidget::show();
}

void Toolbar::submit(bool copyImage) {
    hide();

    QGraphicsScene& scene = appView_.scene();
    //scene.clearSelection();

    VisibleAreaMode& visibleAreaMode = appView_.visibleAreaMode();
    scene.setSceneRect(visibleAreaMode.area.x,
                       visibleAreaMode.area.y,
                       visibleAreaMode.area.width,
                       visibleAreaMode.area.height);

    if (image_ != 0) {
        delete image_;
    }

    image_ = new QImage(scene.sceneRect().size().toSize(), QImage::Format_ARGB32);
    image_->fill(Qt::transparent);

    QPainter painter(image_);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    scene.render(&painter);

    QByteArray bytes;
    QBuffer buffer(&bytes);
    buffer.open(QIODevice::WriteOnly);
    image_->save(&buffer, "PNG");

    appView_.hide();
    appView_.app().setCopyImageToClipboard(copyImage);
    appView_.app().server().upload(bytes);
}

QImage& Toolbar::image() const {
    return *image_;
}

void Toolbar::setSelected(QPushButton* button, bool animate) {
    if (animation_.state() != QAbstractAnimation::Stopped) {
        return;
    }

    if (button == selected_) {
        return;
    }

    selected_ = button;

    if (button == ui->visibleAreaButton) {
        appView_.setMode(ToolbarMode::VISIBLE_AREA);
    } else if (button == ui->lineButton) {
        appView_.setMode(ToolbarMode::LINE);
    } else if (button == ui->arrowButton) {
        appView_.setMode(ToolbarMode::ARROW);
    } else if (button == ui->rectButton) {
        appView_.setMode(ToolbarMode::RECT);
    } else if (button == ui->ellipseButton) {
        appView_.setMode(ToolbarMode::ELLIPSE);
    } else if (button == ui->textButton) {
        appView_.setMode(ToolbarMode::TEXT);
    } else {
        return;
    }

    if (button == ui->textButton) {
        appView_.setCursor(Qt::IBeamCursor);
    } else {
        appView_.setCursor(Qt::CrossCursor);
    }

    int x = ui->selectedCircle->x();
    int y = ui->selectedCircle->y();
    int width = ui->selectedCircle->width();
    int height = ui->selectedCircle->height();

    animation_.setDuration(animate ? 500 : 0);
    animation_.setEndValue(QRect(x, button->y(), width, height));

    animation_.start();
}
