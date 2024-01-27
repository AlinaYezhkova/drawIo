#pragma once

#include <QPainter>

using Position = QPointF;

class ShapeBase
{
protected:

    Position m_position;
    QColor   m_color = Qt::black;
    QColor   m_bgColor = Qt::transparent;

public:
    ShapeBase(Position position, QColor color, QColor bgColor)
        : m_position(position)
        , m_color(color)
        , m_bgColor(bgColor) {}

    Position position() const {
        return m_position;
    }

    void setPosition(Position position) {
        m_position = position;
    }

    virtual void draw(QPainter *painter, const QRectF &rect) = 0;

};

class Circle : public ShapeBase
{
    qreal m_radius;

public:

    Circle(Position position, qreal radius, QColor color, QColor bgColor)
        : ShapeBase(position, color, bgColor), m_radius(radius) {};

    void draw(QPainter *painter, const QRectF &rect) override;

};
