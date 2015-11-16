#ifndef SCREENSHOTGUN_HISTORY_H
#define SCREENSHOTGUN_HISTORY_H

#include <QSettings>
#include "Toolbar.h"

class History : public QObject {
    Q_OBJECT

public:
    History();
    void addLink(const QString&);

    ToolbarMode tool() const;
    QStringList links();

    void lastTool(const ToolbarMode&);
    void links(const QStringList&);

signals:
    void linkAdded(const QString&);

private:
    QSettings settings_;
};

#endif // SCREENSHOTGUN_HISTORY_H
