#ifndef SCREENSHOTGUN_HISTORY_H
#define SCREENSHOTGUN_HISTORY_H

#include <QSettings>
#include "Toolbar.h"

class History {
public:
    History();
    void addLink(const QString&);

    ToolbarMode tool() const;
    QStringList links();

    void lastTool(const ToolbarMode&);
    void links(const QStringList&);

private:
    QSettings settings_;
};

#endif // SCREENSHOTGUN_HISTORY_H
