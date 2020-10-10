#include "Toolbar.h"
#include "src/Context.h"

#include <algorithm>
#include <QClipboard>
#include <QGraphicsScene>
#include <QPushButton>

Toolbar::Toolbar(QWidget* parent) : QWidget(parent), dragging_(false) {
    const Context& ctx = Context::getInstance();

    connect(&ctx.itemManager->visibleAreaItem, &VisibleAreaItem::inited, this, [&]() {
        hide();
    });

    connect(&ctx.itemManager->visibleAreaItem, &VisibleAreaItem::stopped, this, [&]() {
        const int padding = 10;
        const QRect geo = ctx.overlayView->geometry();

        // Width
        const auto& area = ctx.itemManager->visibleAreaItem.area;
        int toolbarX = area.x + area.width + 28;
        int toolbarWidth = ctx.toolbar->width();

        if (toolbarX + toolbarWidth + padding > geo.width()) {
            toolbarX = geo.width() - toolbarWidth - padding;
        }

        // Height
        int toolbarHeight = ctx.toolbar->height();
        int toolbarY = area.y + area.height / 2 - toolbarHeight / 2;
        int screenHeight = geo.height();

        if (toolbarY < padding) {
            toolbarY = padding;
        } else if (toolbarY + toolbarHeight + padding > screenHeight) {
            toolbarY = screenHeight - toolbarHeight - padding;
        }

        setGeometry(toolbarX, toolbarY, toolbarWidth, toolbarHeight);
        show();
    });

    connect(ctx.app, &App::screenshotFinished, this, [&]() {
        hide();
    });

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

    select(ToolbarMode::VISIBLE_AREA);
}

void Toolbar::show() {
    select(Context::getInstance().history->lastTool());
    QWidget::show();
}

ToolbarMode Toolbar::selected() const {
    return selectedMode_;
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

const ToolbarMode Toolbar::mode() const {
    return selectedMode_;
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
        selectedMode_ = ToolbarMode::VISIBLE_AREA;
        emit toolChanged(ToolbarMode::VISIBLE_AREA);
    } else if (button == ui.lineButton) {
        selectedMode_ = ToolbarMode::LINE;
        emit toolChanged(ToolbarMode::LINE);
    } else if (button == ui.arrowButton) {
        selectedMode_ = ToolbarMode::ARROW;
        emit toolChanged(ToolbarMode::ARROW);
    } else if (button == ui.rectButton) {
        selectedMode_ = ToolbarMode::RECT;
        emit toolChanged(ToolbarMode::RECT);
    } else if (button == ui.ellipseButton) {
        selectedMode_ = ToolbarMode::ELLIPSE;
        emit toolChanged(ToolbarMode::ELLIPSE);
    } else if (button == ui.textButton) {
        selectedMode_ = ToolbarMode::TEXT;
        emit toolChanged(ToolbarMode::TEXT);
    } else {
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
