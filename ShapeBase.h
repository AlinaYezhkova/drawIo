#pragma once

#include "qgraphicsscene.h"
#include <QGraphicsItem>
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

    double distance(Position a, Position b);

    virtual void draw(QPainter *painter, const QRectF &rect) = 0;
    virtual bool pointBelongs(Position position) = 0;

};


// TODO: растащить по файлам

class Circle : public ShapeBase
{
    qreal m_radius;

public:

    Circle(Position position, qreal radius, QColor color, QColor bgColor)
        : ShapeBase(position, color, bgColor), m_radius(radius) {};

    void draw(QPainter *painter, const QRectF &rect) override;
    bool pointBelongs(Position position) override;
};

class Square : public ShapeBase
{
    qreal m_side;

public:

    Square(Position position, qreal side, QColor color, QColor bgColor)
        : ShapeBase(position, color, bgColor), m_side(side) {};

    void draw(QPainter *painter, const QRectF &rect) override;
    bool pointBelongs(Position position) override;

    double evaluateBelong(Position p, Position a, Position b) {
        return (b.rx() - a.rx()) * (p.ry() - a.ry()) - (b.ry() - a.ry()) * (p.rx() - a.rx());
    }
};
