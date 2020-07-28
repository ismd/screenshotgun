#pragma once

#include "Toolbar.h"

#include <QSettings>

class History : public QObject {
    Q_OBJECT

public:
    History();
    void addLink(const QString&);

    ToolbarMode tool() const;
    QStringList links();

    void setLastTool(const ToolbarMode &);
    void setLinks(const QStringList &);

signals:
    void linkAdded(const QString&);

private:
    QSettings settings_;
};
