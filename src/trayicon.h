#ifndef TRAYICON_H
#define TRAYICON_H

#include <QSystemTrayIcon>
#include <QAction>
#include <QMenu>

class EditorView;

class TrayIcon : public QSystemTrayIcon
{
    Q_OBJECT

public:
    explicit TrayIcon(EditorView *parent);
    ~TrayIcon();

private:
    EditorView* _editorView;
    QMenu* _iconMenu;
    QAction* _settingsAction;
    QAction* _quitAction;

private slots:
    void showSettings();
};

#endif // TRAYICON_H
