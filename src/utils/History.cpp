#include "History.h"
#include "src/Context.h"

History::History() : settings_("screenshotgun", "history") {
    // Context& ctx = Context::getInstance();

    // connect(&ctx.overlay.toolbar, SIGNAL(onToolChanged(const ToolbarMode)),
    //         this, SLOT(onToolChanged(const ToolbarMode)));
}

void History::addLink(const QString& url) {
    QStringList historyLinks = linksFromHistory();
    std::reverse(std::begin(historyLinks), std::end(historyLinks));

    historyLinks.prepend(url);
    if (historyLinks.size() > 10) {
        historyLinks.removeLast();
    }

    setLinksToHistory(historyLinks);
    emit linkAdded(url);
}

void History::onUploadSuccess(const QString& url) {
    addLink(url);
}

void History::onToolChanged(const ToolbarMode mode) {
    setLastTool(mode);
}

void History::setLastTool(const ToolbarMode& mode) {
  settings_.setValue("last_tool", static_cast<int>(mode));
}

QStringList History::linksFromHistory() {
  QStringList links;
  int size = settings_.beginReadArray("links");

  for (int i = 0; i < size; i++) {
    settings_.setArrayIndex(i);
    links.prepend(settings_.value("link").toString());
  }

  settings_.endArray();
  return links;
}

ToolbarMode History::lastTool() const {
    int value = settings_.value("last_tool", static_cast<int>(ToolbarMode::ARROW)).toInt();

    switch (value) {
        case static_cast<int>(ToolbarMode::LINE):
            return ToolbarMode::LINE;

        case static_cast<int>(ToolbarMode::ARROW):
            return ToolbarMode::ARROW;

        case static_cast<int>(ToolbarMode::RECT):
            return ToolbarMode::RECT;

        case static_cast<int>(ToolbarMode::ELLIPSE):
            return ToolbarMode::ELLIPSE;

        case static_cast<int>(ToolbarMode::TEXT):
            return ToolbarMode::TEXT;

        default:
            return ToolbarMode::ARROW;
    }
}

void History::setLinksToHistory(const QStringList& value) {
    settings_.beginWriteArray("links");

    for (int i = 0; i < value.size(); ++i) {
        settings_.setArrayIndex(i);
        settings_.setValue("link", value.at(i));
    }

    settings_.endArray();
}
