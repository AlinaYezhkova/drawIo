#pragma once

#include "ShapeBase.h"

class Circle : public ShapeBase
{
    qreal m_radius;

public:

    Circle(Position position, qreal radius, QColor color, QColor bgColor)
        : ShapeBase(position, color, bgColor), m_radius(radius) {};

    void draw(QPainter *painter, const QRectF &rect) override;
    bool pointBelongs(Position position) override;
};

