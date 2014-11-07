#ifndef EDITORVIEW_H
#define EDITORVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QSystemTrayIcon>
#include "editorform.h"
#include "settings.h"

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
    void init();
    void run();

private:
    QPixmap _screenshot;
    QGraphicsScene* _scene;
    EditorForm* _editorForm;
    QSystemTrayIcon* _trayIcon;
    Settings* _settings;
};

#endif // EDITORVIEW_H
