#pragma once

#include <QGraphicsView>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include "Document.h"

class CanvasView : public QGraphicsView
{
    Document&   m_doc;
    bool        m_allowDrag = false;
    Position    m_startDragPosition;
    Position    m_startSelectedShapePosition;

public:
    CanvasView(Document& doc, QWidget *parent = nullptr);

protected:
    void drawGrid(QPainter *painter, const QRectF &rect);

    void drawDoc(QPainter *painter, const QRectF &rect);

    void drawBackground(QPainter *painter, const QRectF &rect) override;

    ShapeBase* selectShape (Position position) const;

    void mousePressEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

    void wheelEvent(QWheelEvent* event) override;


};
