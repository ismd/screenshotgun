#include "History.h"
#include <QList>

History::History() : settings_("screenshotgun", "history") {
}

void History::addLink(const QString& url) {
    QStringList historyLinks(links());

    historyLinks.prepend(url);
    if (historyLinks.size() > 10) {
        historyLinks.removeLast();
    }

    links(historyLinks);
}

ToolbarMode History::tool() const {
    int value = settings_.value("last_tool", static_cast<int>(ToolbarMode::ARROW)).toInt();

    switch (value) {
        case static_cast<int>(ToolbarMode::LINE):
            return ToolbarMode::LINE;

        case static_cast<int>(ToolbarMode::ARROW):
            return ToolbarMode::ARROW;

        case static_cast<int>(ToolbarMode::RECT):
            return ToolbarMode::RECT;

        default:
            return ToolbarMode::ARROW;
    }
}

QStringList History::links() {
    QStringList links;
    int size = settings_.beginReadArray("links");

    for (int i = 0; i < size; ++i) {
        settings_.setArrayIndex(i);
        links.append(settings_.value("link").toString());
    }

    settings_.endArray();
    return links;
}

void History::lastTool(const ToolbarMode& value) {
    settings_.setValue("last_tool", static_cast<int>(value));
}

void History::links(const QStringList& value) {
    settings_.beginWriteArray("links");

    for (int i = 0; i < value.size(); ++i) {
        settings_.setArrayIndex(i);
        settings_.setValue("link", value.at(i));
    }

    settings_.endArray();
}
