#ifndef EDITORVIEW_H
#define EDITORVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QSystemTrayIcon>
#include "editorform.h"
#include "settings.h"
#include "server.h"
#include "newversion.h"

class EditorView : public QGraphicsView
{
    Q_OBJECT

public:
    EditorView();
    ~EditorView();
    QGraphicsScene* scene();
    Settings* settings();

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

private slots:
    void run();
    void checkVersion();
    void serverVersion(QString);
    void connectionError();

private:
    void init();
    QPixmap _screenshot;
    QGraphicsScene* _scene;
    EditorForm* _editorForm;
    QSystemTrayIcon* _trayIcon;
    Settings* _settings;
    Server* _server;
    NewVersion* _newVersion;
};

#endif // EDITORVIEW_H
