#pragma once

#include "src/ui/Toolbar.h"

#include <QSettings>

class History : public QObject {
    Q_OBJECT

public:
    History();

    void addLink(const QString&);

    /**
     * Returns list of links from history
     */
    QStringList linksFromHistory();

    /**
     * Returns last used tool
     */
    ToolbarMode lastTool() const;

signals:
    void linkAdded(const QString&);

private:
    void setLastTool(const ToolbarMode&);

    void setLinksToHistory(const QStringList&);

    QSettings settings_;
};
