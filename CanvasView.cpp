#include "CanvasView.h"
#include "QScrollBar"

CanvasView::CanvasView(Document& doc, QWidget *parent) : QGraphicsView(parent), m_doc(doc)
{
    setRenderHint(QPainter::Antialiasing);
    setViewportUpdateMode(FullViewportUpdate);
    setMouseTracking(true);

    //setDragMode(QGraphicsView::ScrollHandDrag);
    //setDragMode(QGraphicsView::RubberBandDrag); -- выделение мышкой
}

void CanvasView::drawGrid(QPainter *painter, const QRectF &rect)
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

void CanvasView::drawDoc(QPainter *painter, const QRectF &rect)
{
    for(auto& shape : m_doc.m_shapes)
    {
        shape->draw(painter, rect);
    }
}

void CanvasView::drawBackground(QPainter *painter, const QRectF &rect)
{
    QGraphicsView::drawBackground(painter, rect);
    drawGrid(painter, rect);
    drawDoc(painter, rect);
}

ShapeBase* CanvasView::selectShape (Position position) const
{
    for(auto it = m_doc.m_shapes.rbegin(); it != m_doc.m_shapes.rend(); ++it)
    {
        if((*it)->pointBelongs(position)){
            return (*it);
        }
    }
    return nullptr;
}

void CanvasView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        Position mousePosition = mapToScene(event->pos());
        m_doc.m_selectedShape = selectShape(mousePosition);
        m_allowDrag = true;
        m_startDragPosition = mousePosition;
        if(m_doc.m_selectedShape) {
            m_startSelectedShapePosition = m_doc.m_selectedShape->position();
        }
        else {
            m_startSelectedShapePosition = m_doc.m_offset;
            setCursor(Qt::ClosedHandCursor);
        }
    }
    QGraphicsView::mousePressEvent(event);
}

void CanvasView::mouseMoveEvent(QMouseEvent *event)
{
    if(m_allowDrag) {
        Position mousePosition = mapToScene(event->pos());
        if(m_doc.m_selectedShape) {
            m_doc.m_selectedShape->setPosition(mousePosition + m_startSelectedShapePosition - m_startDragPosition);
        }
        else {
            // Calculate the distance moved by the mouse
            QPointF delta = mousePosition - m_startDragPosition;

            // Adjust the position of the view
            QPoint newCenter = viewport()->rect().center() - delta.toPoint();
            centerOn(mapToScene(newCenter));        }
        QRectF sceneRect = mapToScene(viewport()->rect()).boundingRect();
        updateScene({sceneRect});
    }
    QGraphicsView::mouseMoveEvent(event);
}

void CanvasView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_allowDrag = false;
        m_doc.m_selectedShape = nullptr;
        setCursor(Qt::ArrowCursor);
    }
    QGraphicsView::mouseReleaseEvent(event);
}

void CanvasView::wheelEvent(QWheelEvent* event)
{
    if (event->modifiers() == Qt::ControlModifier) {
        // Calculate the scaling factor based on the mouse wheel delta
        m_doc.m_scale = 1.15; // Adjust this value to control the zoom speed
        if (event->angleDelta().y() < 0) {
            m_doc.m_scale = 1.0 / m_doc.m_scale;
        }
        // Apply the scaling transformation to the view
        //            QPoint mousePos = event->position().toPoint();
        //            QPointF scenePos = mapToScene(mousePos);
        scale(m_doc.m_scale, m_doc.m_scale);
        //            QPointF newScenePos = mapToScene(mousePos);

        // Translate the view to keep the scene position under the mouse fixed
        //            QPointF translation = newScenePos - scenePos;
        //            translate(translation.x(), translation.y());
    }
    else {
        QGraphicsView::wheelEvent(event);
    }
}

