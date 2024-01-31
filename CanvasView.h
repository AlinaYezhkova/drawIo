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

public:
    CanvasView(Document& doc, QWidget *parent = nullptr) : QGraphicsView(parent), m_doc(doc)
    {
        setRenderHint(QPainter::Antialiasing);
        setViewportUpdateMode(FullViewportUpdate);
        setMouseTracking(true);

        //setDragMode(QGraphicsView::ScrollHandDrag);
        //setDragMode(QGraphicsView::RubberBandDrag); -- выделение мышкой
    }

protected:
    void drawGrid(QPainter *painter, const QRectF &rect)
    {
        int gridSize = 50; // Grid spacing
        QColor gridColor = Qt::black;

        // Get the top-left position of the visible area in scene coordinates
        QPointF topLeftScene = mapToScene(rect.topLeft().toPoint());

        // Calculate the starting points for the horizontal and vertical grid lines
        int startX = int(topLeftScene.x()) - (int(topLeftScene.x()) % gridSize);
        int startY = int(topLeftScene.y()) - (int(topLeftScene.y()) % gridSize);

        // Draw the vertical lines
        for (qreal x = startX; x < rect.right(); x += gridSize) {
            QLineF line(x, rect.top(), x, rect.bottom());
            painter->setPen(QPen(gridColor, 0.5));
            painter->drawLine(line);
        }

        // Draw the horizontal lines
        for (qreal y = startY; y < rect.bottom(); y += gridSize) {
            QLineF line(rect.left(), y, rect.right(), y);
            painter->setPen(QPen(gridColor, 0.5));
            painter->drawLine(line);
        }
    }

    void drawDoc(QPainter *painter, const QRectF &rect)
    {
        for(auto& shape : m_doc.m_shapes)
        {
            shape->draw(painter, rect);
        }
    }

    void drawBackground(QPainter *painter, const QRectF &rect) override
    {
        QGraphicsView::drawBackground(painter, rect);
        drawGrid(painter, rect);
        drawDoc(painter, rect);
    }

    ShapeBase* selectShape (Position position) const
    {
        for(auto& shape : m_doc.m_shapes)
        {
            if(shape->pointBelongs(position)){
                return shape;
            }
        }

        // TODO: make Document ShapeBase ?! For dragging around
        return m_doc.m_shapes.back();
    }

    void mousePressEvent(QMouseEvent *event) override
    {
        if (event->button() == Qt::LeftButton) {
            Position mousePosition = mapToScene(event->pos());
            m_doc.m_selectedShape = selectShape(mousePosition);
            m_allowDrag = true;
            m_doc.m_selectedShape->setPosition(mousePosition);
        }
        QGraphicsView::mousePressEvent(event);
    }

    void mouseMoveEvent(QMouseEvent *event) override {
        if(m_allowDrag) {
            Position mousePosition = mapToScene(event->pos());
            m_doc.m_selectedShape->setPosition(mousePosition);
            QRectF sceneRect = mapToScene(viewport()->rect()).boundingRect();
            updateScene({sceneRect});
        }
        QGraphicsView::mouseMoveEvent(event);
    }

    void mouseReleaseEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            m_allowDrag = false;
//            Position mousePosition = mapToScene(event->pos());
//            ShapeBase* shapeToMove = m_doc.m_shapes.back();
//            // TODO: select shapeToMove from vector according to position
//            shapeToMove->setPosition(mousePosition);
//            this->viewport()->update();
        }

        QGraphicsView::mouseReleaseEvent(event);
    }


};
