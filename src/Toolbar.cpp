#include <QGraphicsScene>
#include "App.h"
#include "Toolbar.h"
#include "ui_Toolbar.h"

Toolbar::Toolbar(AppView& appView)
    : QWidget(&appView),
      ui(new Ui::Toolbar),
      appView_(appView),
      dragging_(false) {

    hide();
    ui->setupUi(this);
    ui->selectedCircle->lower();

    appView_.setMouseTracking(true);

    setSelected(ui->visibleAreaButton);
    buttons_.append(ui->visibleAreaButton);
    buttons_.append(ui->rectButton);
    buttons_.append(ui->lineButton);
    buttons_.append(ui->arrowButton);
}

Toolbar::~Toolbar() {
    delete ui;
}

AppView& Toolbar::appView() {
    return appView_;
}

void Toolbar::select(ToolbarMode mode) {
    switch (mode) {
        case ToolbarMode::VISIBLE_AREA:
            setSelected(ui->visibleAreaButton);
            break;

        case ToolbarMode::LINE:
            setSelected(ui->lineButton);
            break;

        case ToolbarMode::ARROW:
            setSelected(ui->arrowButton);
            break;

        case ToolbarMode::RECT:
            setSelected(ui->rectButton);
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
    appView_.setMouseTracking(!appView_.visibleAreaMode().initialized());
}

void Toolbar::on_lineButton_clicked() {
    setSelected(ui->lineButton);
    appView_.setMouseTracking(false);
}

void Toolbar::on_arrowButton_clicked() {
    setSelected(ui->arrowButton);
    appView_.setMouseTracking(false);
}

void Toolbar::on_rectButton_clicked() {
    setSelected(ui->rectButton);
    appView_.setMouseTracking(false);
}

void Toolbar::on_okButton_clicked() {
    appView_.hide();
    hide();

    QGraphicsScene& scene = appView_.scene();
    //scene.clearSelection();

    VisibleAreaMode& visibleAreaMode = appView_.visibleAreaMode();
    scene.setSceneRect(visibleAreaMode.area.x,
                       visibleAreaMode.area.y,
                       visibleAreaMode.area.width,
                       visibleAreaMode.area.height);

    QImage image(scene.sceneRect().size().toSize(), QImage::Format_ARGB32);
    image.fill(Qt::transparent);

    QPainter painter(&image);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    scene.render(&painter);

    QByteArray bytes;
    QBuffer buffer(&bytes);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "PNG");

    appView_.app().server().upload(bytes);
}

void Toolbar::show() {
    setSelected(ui->arrowButton, false);
    QWidget::show();
}

void Toolbar::setSelected(QPushButton* const button, bool animate) {
    selected_ = button;

    if (button == ui->visibleAreaButton) {
        appView_.mode(ToolbarMode::VISIBLE_AREA);
    } else if (button == ui->lineButton) {
        appView_.mode(ToolbarMode::LINE);
    } else if (button == ui->arrowButton) {
        appView_.mode(ToolbarMode::ARROW);
    } else if (button == ui->rectButton) {
        appView_.mode(ToolbarMode::RECT);
    }

    int x = ui->selectedCircle->x();
    int y = ui->selectedCircle->y();
    int width = ui->selectedCircle->width();
    int height = ui->selectedCircle->height();

    QPropertyAnimation* animation = new QPropertyAnimation(ui->selectedCircle, "geometry");
    animation->setDuration(animate ? 500 : 0);
    animation->setStartValue(QRect(x, y, width, height));
    animation->setEndValue(QRect(x, button->y(), width, height));

    animation->start();
}
