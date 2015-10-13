#ifndef TRAYICON_H
#define TRAYICON_H

#include <QAction>
#include <QMenu>
#include <QSystemTrayIcon>

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
    QAction* _makeScreenshotAction;
    QAction* _settingsAction;
    QAction* _quitAction;

signals:
    void makeScreenshot();

private slots:
    void makeScreenshotAction();
    void showSettings();
};

#endif // TRAYICON_H
