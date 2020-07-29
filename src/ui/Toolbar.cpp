#include "Toolbar.h"
#include "src/Context.h"

#include <algorithm>
#include <QClipboard>
#include <QGraphicsScene>
#include <QPushButton>

Toolbar::Toolbar() : dragging_(false) {
    hide();
    ui.setupUi(this);
    ui.selectedCircle->lower();
    setFocusPolicy(Qt::ClickFocus);

    buttons_ = {
      ui.visibleAreaButton,
      ui.ellipseButton,
      ui.rectButton,
      ui.lineButton,
      ui.arrowButton,
      ui.textButton,
    };

    animation_.setTargetObject(ui.selectedCircle);
    animation_.setPropertyName("geometry");
}

void Toolbar::select(const ToolbarMode mode) {
    return select(mode, false);
}

void Toolbar::select(const ToolbarMode mode, bool withAnimation) {
    switch (mode) {
        case ToolbarMode::VISIBLE_AREA:
            setSelectedButton(ui.visibleAreaButton, withAnimation);
            break;

        case ToolbarMode::LINE:
            setSelectedButton(ui.lineButton, withAnimation);
            break;

        case ToolbarMode::ARROW:
            setSelectedButton(ui.arrowButton, withAnimation);
            break;

        case ToolbarMode::RECT:
            setSelectedButton(ui.rectButton, withAnimation);
            break;

        case ToolbarMode::ELLIPSE:
            setSelectedButton(ui.ellipseButton, withAnimation);
            break;

        case ToolbarMode::TEXT:
            setSelectedButton(ui.textButton, withAnimation);
            break;
    }
}

void Toolbar::selectNext() {
    const auto selected = getSelected();

    if (selected == buttons_.cend()) {
        return;
    }

    setSelectedButton(*(selected + 1));
}

void Toolbar::selectPrevious() {
    const auto selected = getSelected();

    if (selected == buttons_.cbegin()) {
        return;
    }

    setSelectedButton(*(selected - 1));
}

void Toolbar::mousePressEvent(QMouseEvent* event) {
    const QRect dragLabelGeometry = ui.dragLabel->geometry();

    int x = event->x(),
        y = event->y(),
        dragLabelX = dragLabelGeometry.x(),
        dragLabelY = dragLabelGeometry.y();

    if (x < dragLabelX
        || x > dragLabelX + dragLabelGeometry.width()
        || y < dragLabelY
        || y > dragLabelY + dragLabelGeometry.height()
    ) {
        return;
    }

    initDragCoords_.x = x;
    initDragCoords_.y = y;
    dragging_ = true;
}

// void Toolbar::submit() {
//     hide();
//     QApplication::clipboard()->setText("");

//     QGraphicsScene& scene = context_.overlay().scene();

//     VisibleAreaMode& visibleAreaMode = context_.overlay().visibleAreaMode();
//     scene.setSceneRect(visibleAreaMode.area.x,
//                        visibleAreaMode.area.y,
//                        visibleAreaMode.area.width,
//                        visibleAreaMode.area.height);

//     if (image_ != 0) {
//         delete image_;
//     }

//     image_ = new QImage(scene.sceneRect().size().toSize(), QImage::Format_ARGB32);
//     image_->fill(Qt::transparent);

//     QPainter painter(image_);
//     painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
//     scene.render(&painter);

//     QByteArray bytes;
//     QBuffer buffer(&bytes);
//     buffer.open(QIODevice::WriteOnly);
//     image_->save(&buffer, "PNG");

//     overlay_.hide();

//     switch (overlay_.app().uploadService()) {
//         case UploadService::SERVER:
//             overlay_.app().server().upload(bytes);
//             break;

//         case UploadService::DROPBOX:
//             overlay_.app().dropbox().upload(bytes);
//             break;

//         case UploadService::YANDEX:
//             overlay_.app().yandex().upload(bytes);
//             break;

//         case UploadService::GOOGLE:
//             overlay_.app().google().upload(bytes);
//             break;

//         case UploadService::CLIPBOARD:
//             overlay_.app().copyImageToClipboard();
//             break;
//     }
// }

void Toolbar::mouseMoveEvent(QMouseEvent* event) {
    move(geometry().x() + event->x() - initDragCoords_.x,
        geometry().y() + event->y() - initDragCoords_.y);
}

void Toolbar::mouseReleaseEvent(QMouseEvent* event) {
    dragging_ = false;
}

void Toolbar::on_visibleAreaButton_clicked() {
    setSelectedButton(ui.visibleAreaButton);
}

void Toolbar::on_lineButton_clicked() {
    setSelectedButton(ui.lineButton);
}

void Toolbar::on_arrowButton_clicked() {
    setSelectedButton(ui.arrowButton);
}

void Toolbar::on_rectButton_clicked() {
    setSelectedButton(ui.rectButton);
}

void Toolbar::on_ellipseButton_clicked() {
    setSelectedButton(ui.ellipseButton);
}

void Toolbar::on_textButton_clicked() {
    setSelectedButton(ui.textButton);
}

void Toolbar::on_okButton_clicked() {
    emit screenshotButtonClicked();
}

const std::vector<QPushButton*>::const_iterator Toolbar::getSelected() const {
    return std::find_if(buttons_.begin(), buttons_.end(), [&](const QPushButton* item) { return item == selected_; });
}

void Toolbar::setSelectedButton(QPushButton* button, bool animate) {
    if (animation_.state() != QAbstractAnimation::Stopped) {
        return;
    }

    if (selected_ == button) {
        return;
    }

    selected_ = button;

    if (button == ui.visibleAreaButton) {
        emit toolChanged(ToolbarMode::VISIBLE_AREA);
    } else if (button == ui.lineButton) {
        emit toolChanged(ToolbarMode::LINE);
    } else if (button == ui.arrowButton) {
        emit toolChanged(ToolbarMode::ARROW);
    } else if (button == ui.rectButton) {
        emit toolChanged(ToolbarMode::RECT);
    } else if (button == ui.ellipseButton) {
        emit toolChanged(ToolbarMode::ELLIPSE);
    } else if (button == ui.textButton) {
        emit toolChanged(ToolbarMode::TEXT);
    } else {
        qDebug() << "Bad tool";
        return;
    }

    const QRect endValue(
       ui.selectedCircle->x(),
       button->y(),
       ui.selectedCircle->width(),
       ui.selectedCircle->height()
    );

    animation_.setDuration(animate ? 500 : 0);
    animation_.setEndValue(endValue);

    animation_.start();
}
