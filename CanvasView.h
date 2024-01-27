#pragma once

#include <QGraphicsView>
#include <QPainter>
#include "Document.h"

class CanvasView : public QGraphicsView
{
    Document& m_doc;

public:
    CanvasView(Document& doc, QWidget *parent = nullptr) : QGraphicsView(parent), m_doc(doc)
    {
        setRenderHint(QPainter::Antialiasing);
        setViewportUpdateMode(FullViewportUpdate);
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
};
