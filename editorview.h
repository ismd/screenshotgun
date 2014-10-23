#ifndef EDITORVIEW_H
#define EDITORVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>

#include "editorform.h"

class EditorView : public QGraphicsView
{
public:
    EditorView();
    ~EditorView();

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

private:
    QPixmap screenshot;
    QGraphicsScene *scene;
    EditorForm *editorForm;
};

#endif // EDITORVIEW_H
